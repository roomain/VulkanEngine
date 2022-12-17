#pragma once
#include "vulkan/vulkan.h"
#include <utility>

/*@brief functions for structure initialisation*/
namespace Vulkan::Initializers
{
	[[nodiscard]] constexpr VkViewport&& viewport(const float a_x, const float a_y, const float a_width, const float a_height, const float a_near, const float a_far)
	{
		return VkViewport{ a_x, a_y, a_width, a_height, a_near, a_far };
	}

	[[nodiscard]] constexpr VkExtent2D&& extent2D(const uint32_t a_width, const uint32_t a_height)
	{
		return VkExtent2D{ a_width, a_height };
	}

	[[nodiscard]] constexpr VkOffset2D offset2D(const int32_t a_x, const int32_t a_y)
	{
		return VkOffset2D{ a_x, a_y };
	}

	[[nodiscard]] constexpr VkExtent3D&& extent3D(const uint32_t a_width, const uint32_t a_height, const uint32_t a_depth)
	{
		return VkExtent3D{ a_width, a_height, a_depth };
	}

	[[nodiscard]] constexpr VkOffset3D offset3D(const int32_t a_x, const int32_t a_y, const int32_t a_z)
	{
		return VkOffset3D{ a_x, a_y, a_z };
	}
	
	[[nodiscard]] constexpr VkRect2D&& rect2D(const int32_t a_x, const int32_t a_y, const uint32_t a_width, const uint32_t a_height)
	{
		return VkRect2D{ std::move(offset2D(a_x, a_y)), std::move(extent2D(a_width, a_height))};
	}

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