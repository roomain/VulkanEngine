#include "pch.h"
#include "SceneComponent.h"


void SceneComponent::writeCommand(VkCommandBuffer a_commandBufferHandle)const
{
    internalWriteCommand(a_commandBufferHandle);
    for (const auto& child : m_children)
        child->writeCommand(a_commandBufferHandle);
}

bool SceneComponent::contains(const SceneComponentPtr& a_child)const
{
    return std::ranges::find(m_children, a_child) != m_children.cend();
}

void SceneComponent::addChild(const SceneComponentPtr& a_child)
{
    if (contains(a_child))
        return;

    if (auto oldParent = a_child->m_parent.lock())
    {
        // remove from old parent
        if (auto iter = std::ranges::find(oldParent->m_children, a_child); iter != oldParent->m_children.cend())
            oldParent->m_children.erase(iter);
    }
    a_child->m_parent = weak_from_this();
    m_children.push_back(a_child);
}

void SceneComponent::foreach(const std::function<void(const SceneComponentPtr&)>& a_operator)const
{
    for (const auto& node : m_children)
        a_operator(node);
}