#pragma once
/***********************************************
* @headerfile SceneComponent.h
* @date 29 / 03 / 2025
* @author Roomain
************************************************/
#include <vector>
#include <memory>
#include <ranges>
#include <functional>
#include <type_traits>
#include "vulkan/vulkan.hpp"
#include "common/notCopiable.h"
#include "Rtti_macros.h"

class SceneComponent;
using SceneComponentWPtr = std::weak_ptr<SceneComponent>;
using SceneComponentPtr = std::shared_ptr<SceneComponent>;

class SceneComponent : public std::enable_shared_from_this<SceneComponent>
{
    DECLARE_RTTI(1, SceneComponent)
public:    
    using SceneComponentIterator = std::vector<SceneComponentPtr>::iterator;
    using SceneComponentConst_Iterator = std::vector<SceneComponentPtr>::const_iterator;

protected:
    virtual void internalWriteCommand(VkCommandBuffer a_commandBufferHandle)const = 0;

private:
    SceneComponentWPtr m_parent;
    std::vector<SceneComponentPtr> m_children;

    inline SceneComponentIterator internFind(const SceneComponent* a_child)
    {
        return std::ranges::find_if(m_children, [a_child](const SceneComponentPtr& a_node)
                {
                    return a_node.get() == a_child;
                });
    }

public:
    NOT_COPIABLE(SceneComponent)
    SceneComponent() = default;
    virtual ~SceneComponent()
    {
        if(auto oldParent = m_parent.lock())
        {
            // remove from old parent
            if(auto iter = oldParent->internFind(this); iter != oldParent->m_children.cend())
                oldParent->m_children.erase(iter);
        }
    }

    bool contains(const SceneComponentPtr& a_child)const;
    void addChild(const SceneComponentPtr& a_child);
    void foreach(const std::function<void(const SceneComponentPtr&)>& a_operator)const;

    template<typename Component> requires std::is_base_of_v<SceneComponent, Component>
    std::vector<std::shared_ptr<Component>> find()const
    {
        std::vector<std::shared_ptr<Component>> nodeFound;
        for (const auto& node : m_children)
        {
            if (node->isKindOf<Component>())
                nodeFound.emplace_back(node->cast<Component>());
            nodeFound.emplace_back(node->find<Component>());
        }
        return nodeFound;
    }

	template<typename Type> requires std::is_base_of_v<SceneComponent,Type>
    void foreach(const std::function<void(const std::shared_ptr<Type>&)>& a_operator)const
    {
        for (const auto& node : m_children)
        {
            if (auto typeNode = node->cast<Type>(); typeNode.isValid())
                a_operator(typeNode);
                
            node->foreach<Type>(a_operator);
        }
    }

    virtual void tick(const float a_deltaSec) = 0;
    virtual void writeCommand(VkCommandBuffer a_commandBufferHandle)const = 0;

    inline SceneComponentWPtr parent()const { return m_parent; }
    inline SceneComponentIterator begin(){ return m_children.begin(); }
    inline SceneComponentIterator end(){ return m_children.end(); }
    inline SceneComponentConst_Iterator cbegin()const{ return m_children.cbegin(); }
    inline SceneComponentConst_Iterator cend()const{ return m_children.cend(); }    
};
