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
	VkInstance instanceHandle = VK_NULL_HANDLE;
};

struct VulkanDeviceContext : VulkanInstanceContext
{
	int deviceIndex = -1;								/*!< device index in context*/
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;	/*!< physical device handle*/
	VkDevice logicalDevice = VK_NULL_HANDLE;			/*!< logical device handle*/
};

struct VulkanSwapChainContext : VulkanDeviceContext
{
	VkSurfaceKHR surface = VK_NULL_HANDLE;
	VkSwapchainKHR swapChain = VK_NULL_HANDLE;
};