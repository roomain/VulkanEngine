#pragma once
/***********************************************
* @headerfile VulkanLocalsContexts.h
* @date 03 / 12 / 2024
* @author Roomain
************************************************/
#include <vulkan/vulkan.hpp>

/*@brief structures representing differnt level of a vulkan context*/
struct VulkanInstanceContext
{
	VkInstance instanceHandle;
};

struct VulkanDeviceContext : VulkanInstanceContext
{
	VkPhysicalDevice physicalDevice;
	VkDevice logicalDevice;
};