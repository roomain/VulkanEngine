#pragma once
#include <string>
#include <vector>
#include "Reflection/JsonReflection/deserialize_functions.h"
#include "Reflection/JsonReflection/deserialize_macros.h"

#include "VulkanParameter.generated.h"

REFLECT_CLASS(VulkanParameter)
struct VulkanParameter
{
	DESERIALIZE_DECLARE(VulkanParameter)
	bool bIsDebug = true;
	REFLECT_MEMBER
	std::vector<std::string> extensions;	/*!< vulkan instance extensions properties*/
	REFLECT_MEMBER
	std::vector<std::string> layers;		/*!< vulkan instance desired layer*/
};

DESERIALIZE_IMPL(VulkanParameter)



REFLECT_CLASS(VulkanQueueFamilyParameter)
struct VulkanQueueFamilyParameter
{
	DESERIALIZE_DECLARE(VulkanQueueFamilyParameter)
	REFLECT_MEMBER
	bool bIsRenderer = true;	/*!< is rendering queue*/
	REFLECT_MEMBER
	VkQueueFlags flags;			/*!< queue flags*/
	REFLECT_MEMBER
	uint32_t count;				/*!< number of queue*/
};

DESERIALIZE_IMPL(VulkanQueueFamilyParameter)




REFLECT_CLASS(VulkanDeviceParameter)
struct VulkanDeviceParameter
{
	DESERIALIZE_DECLARE(VulkanDeviceParameter)
	REFLECT_MEMBER
	std::vector<std::string> extensions;			/*!< vulkan device extensions properties*/
	REFLECT_MEMBER
	std::vector<std::string> layers;				/*!< vulkan device desired layer*/
	REFLECT_MEMBER
	std::vector<VulkanQueueFamilyParameter> queues;	/*!< vulkan queue family parameters*/
};

DESERIALIZE_IMPL(VulkanDeviceParameter)