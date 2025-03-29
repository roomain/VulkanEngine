#pragma once
/***********************************************
* @headerfile EngineTreeNode.h
* @date 24 / 03 / 2025
* @author Roomain
************************************************/
// Type your code here, or load an example.
#include <vector>
#include <memory>
#include <ranges>
#include <functional>

class EngineTreeNode;
using EngineTreeNodeWPtr = std::weak_ptr<EngineTreeNode>;
using EngineTreeNodePtr = std::shared_ptr<EngineTreeNode>;

class EngineTreeNode : public std::enable_shared_from_this<EngineTreeNode>
{
public:    
    using EngineTreeNodeIterator = std::vector<EngineTreeNodePtr>::iterator;
    using EngineTreeNodeConst_Iterator = std::vector<EngineTreeNodePtr>::const_iterator;

private:
    EngineTreeNodeWPtr m_parent;
    std::vector<EngineTreeNodePtr> m_children;

    inline EngineTreeNodeIterator internFind(const EngineTreeNode* a_child)
    {
        return std::ranges::find_if(m_children, [a_child](const EngineTreeNodePtr& a_node)
                {
                    return a_node.get() == a_child;
                });
    }

public:
    EngineTreeNode() = default;
    virtual ~EngineTreeNode()
    {
        if(auto oldParent = m_parent.lock())
        {
            // remove from old parent
            if(auto iter = oldParent->internFind(this); iter != oldParent->m_children.cend())
                oldParent->m_children.erase(iter);
        }
    }

    inline EngineTreeNodeWPtr parent()const{ return m_parent; }

    inline bool contains(const EngineTreeNodePtr& a_child)const
    {
        return std::ranges::find(m_children, a_child) != m_children.cend();
    }

    void addChild(const EngineTreeNodePtr& a_child)
    {
        if(contains(a_child))
            return;

        if(auto oldParent = a_child->m_parent.lock())
        {
            // remove from old parent
            if(auto iter = std::ranges::find(oldParent->m_children, a_child); iter != oldParent->m_children.cend())
                oldParent->m_children.erase(iter);
        }
        a_child->m_parent = weak_from_this();
        m_children.push_back(a_child);
    }

    inline void foreach(const std::function<void(const EngineTreeNodePtr&)>& a_operator)const
    {
        for(const auto& node : m_children)
            a_operator(node);
    }

    inline EngineTreeNodeIterator begin(){ return m_children.begin(); }
    inline EngineTreeNodeIterator end(){ return m_children.end(); }
    inline EngineTreeNodeConst_Iterator cbegin()const{ return m_children.cbegin(); }
    inline EngineTreeNodeConst_Iterator cend()const{ return m_children.cend(); }
};

