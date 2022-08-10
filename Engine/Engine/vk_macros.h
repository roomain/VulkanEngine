#pragma once
#include "vulkan/vulkan.h"
#include "vk_Exception.h"
#include "vk_string.h"


#define VK_CHECK(funRes) \
if(funRes != VK_SUCCESS) \
{\
	throw Vulkan::VK_Exception(Vulkan::to_string(static_cast<VkResult>(funRes)) + " for call " + #funRes, std::source_location::current()); \
}