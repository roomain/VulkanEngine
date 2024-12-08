#pragma once
/***********************************************
* @headerfile VulkanObject.h
* @date 03 / 12 / 2024
* @author Roomain
************************************************/
#include <type_traits>
#include "VulkanLocalsContexts.h"

/*@brief base class of vulkan object wich contains a local context*/
template<typename Context> requires std::is_base_of_v<VulkanInstanceContext, Context>
class VulkanObject
{
protected:
	Context m_ctxt;	/*!< vulkan local context*/

public:
	VulkanObject() = delete;
	explicit VulkanObject(const Context& a_ctxt) : m_ctxt{a_ctxt}{}
	explicit VulkanObject(Context&& a_ctxt)noexcept : m_ctxt{ a_ctxt } {}
	[[nodiscard]] Context vulkanContext()const noexcept { return m_ctxt; }
};
