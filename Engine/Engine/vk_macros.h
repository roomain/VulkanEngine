#pragma once
#include "vulkan/vulkan.h"
#include "vk_Exception.h"
#include "vk_enum_to_string.h"


#ifdef _DEBUG
#define VK_CHECK(funRes) \
if(funRes != VK_SUCCESS) \
{\
	throw Vulkan::VK_Exception(to_string(static_cast<VkResult>(funRes)) + " for call " + #funRes, std::source_location::current()); \
}
#else
#define VK_CHECK(funRes)
#endif