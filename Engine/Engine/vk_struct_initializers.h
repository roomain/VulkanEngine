#pragma once
#include "vulkan/vulkan.h"

/*@brief functions for structure initialisation*/
namespace Vulkan::Initializers
{
	inline VkApplicationInfo&& applicationInfo()
	{
		return VkApplicationInfo{ .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO, .pNext = nullptr };
	}

	inline VkInstanceCreateInfo&& instanceCreateInfo()
	{
		return VkInstanceCreateInfo{ .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, .pNext = nullptr, .flags = 0 };
	}

	inline VkDebugReportCallbackCreateInfoEXT&& debugCallbackCreateInfo()
	{
		return VkDebugReportCallbackCreateInfoEXT{ .sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT };
	}

	inline VkDebugUtilsMessengerCreateInfoEXT&& messageCallbackCreateInfo()
	{
		return VkDebugUtilsMessengerCreateInfoEXT{ .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT, .pNext = nullptr , .pUserData = nullptr};
	}

	inline VkDeviceCreateInfo&& deviceCreateInfo()
	{
		return VkDeviceCreateInfo{ .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO, .pNext = nullptr };
	}

	inline VkDeviceQueueCreateInfo&& queueCreateInfo()
	{
		return VkDeviceQueueCreateInfo{ .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO };
	}

	inline VkSwapchainCreateInfoKHR&& swapChainCreateInfoKHR()
	{
		return VkSwapchainCreateInfoKHR{ .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR };
	}

	inline VkMemoryAllocateInfo&& memoryAllocateInfo()
	{
		return VkMemoryAllocateInfo{ .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO, .pNext = nullptr };
	}
	
	inline VkCommandBufferAllocateInfo&& commandBufferCreateInfo()
	{
		return VkCommandBufferAllocateInfo{ .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO, .pNext = nullptr };
	}

	inline VkCommandBufferBeginInfo&& commandBufferBeginInfo()
	{
		return VkCommandBufferBeginInfo{ .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO, .pNext = nullptr };
	}

	inline VkSubmitInfo&& dubmitInfo()
	{
		return VkSubmitInfo{ .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO, .pNext = nullptr };
	}
}