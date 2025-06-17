#pragma once
/***********************************************
* @headerfile Vulkan_macros.h
* @date 25 / 08 / 2024
* @author Roomain
************************************************/
#include "LoggingSystem/Exception.h"
#include "LoggingSystem/logger.h"
#include "vulkan_enum_to_string.h"
#include "vulkan/vulkan_core.h"

#define VK_CHECK_EXCEPT(vkCall) \
if (const VkResult result = vkCall; result != VK_SUCCESS) \
	throw Exception(#vkCall##": " + to_string(result));

#define VK_CHECK_LOG(vkCall) \
if (const VkResult result = vkCall; result != VK_SUCCESS) \
	Logger::info(#vkCall##": " + to_string(result));
