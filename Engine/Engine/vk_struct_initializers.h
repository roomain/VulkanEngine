#pragma once
#include "vulkan/vulkan.h"

/*@brief functions for structure initialisation*/
namespace Vulkan::Initializers
{
	[[nodiscard]] constexpr VkApplicationInfo&& applicationInfo()
	{
		return std::move(VkApplicationInfo{ .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO, .pNext = nullptr });
	}

	[[nodiscard]] constexpr VkInstanceCreateInfo&& instanceCreateInfo()
	{
		return std::move(VkInstanceCreateInfo{ .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, .pNext = nullptr, .flags = 0 });
	}

	[[nodiscard]] constexpr VkDebugReportCallbackCreateInfoEXT&& debugCallbackCreateInfo()
	{
		return std::move(VkDebugReportCallbackCreateInfoEXT{ .sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT });
	}

	[[nodiscard]] constexpr VkDebugUtilsMessengerCreateInfoEXT&& messageCallbackCreateInfo()
	{
		return std::move(VkDebugUtilsMessengerCreateInfoEXT{ .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT, .pNext = nullptr , .pUserData = nullptr});
	}

	[[nodiscard]] constexpr VkDeviceCreateInfo&& deviceCreateInfo()
	{
		return std::move(VkDeviceCreateInfo{ .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO, .pNext = nullptr });
	}

	[[nodiscard]] constexpr VkDeviceQueueCreateInfo&& queueCreateInfo()
	{
		return std::move(VkDeviceQueueCreateInfo{ .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO });
	}

	[[nodiscard]] constexpr VkSwapchainCreateInfoKHR&& swapChainCreateInfoKHR()
	{
		return std::move(VkSwapchainCreateInfoKHR{ .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR });
	}

	[[nodiscard]] constexpr VkMemoryAllocateInfo&& memoryAllocateInfo()
	{
		return std::move(VkMemoryAllocateInfo{ .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO, .pNext = nullptr, .allocationSize = 0 });
	}
	
	[[nodiscard]] constexpr VkCommandBufferAllocateInfo&& commandBufferCreateInfo()
	{
		return std::move(VkCommandBufferAllocateInfo{ .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO, .pNext = nullptr });
	}

	[[nodiscard]] constexpr VkCommandBufferBeginInfo&& commandBufferBeginInfo()
	{
		return std::move(VkCommandBufferBeginInfo{ .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO, .pNext = nullptr });
	}

	[[nodiscard]] constexpr VkSubmitInfo&& dubmitInfo()
	{
		return std::move(VkSubmitInfo{ .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO, .pNext = nullptr });
	}

	[[nodiscard]] constexpr VkImageViewCreateInfo&& imageViewCreateInfo()
	{
		return std::move(VkImageViewCreateInfo{ .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO, .pNext = nullptr });
	}

	[[nodiscard]] constexpr VkImageCreateInfo&& imageCreateInfo()
	{
		return std::move(VkImageCreateInfo{ .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO, .pNext = nullptr, .imageType = VK_IMAGE_TYPE_2D });
	}

	[[nodiscard]] constexpr VkBufferCreateInfo&& bufferCreateInfo()
	{
		return std::move(VkBufferCreateInfo{ .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO, .pNext = nullptr, .queueFamilyIndexCount = 0, .pQueueFamilyIndices = nullptr });
	}
}