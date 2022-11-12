#pragma once
#include "vulkan/vulkan.h"
#include <string>
#include <vector>
#include <memory>

namespace Vulkan
{
	class VK_WindowSystemProxy;
	struct Device;
	struct RendererQueuesConfiguration;
	struct VulkanConfiguration;

	void createVulkanInstance(const VulkanConfiguration& a_conf, VkInstance& a_vkInstance);

	void createVulkanDevice(const RendererQueuesConfiguration& a_queueConf, const std::vector<std::string>& a_deviceExt, Device& a_device);

	void createSwapChain(const Device& a_device, VkSwapchainKHR& a_swapChain, VkSurfaceFormatKHR& a_surfaceFormat, std::unique_ptr<VK_WindowSystemProxy>&& a_windowProxy);

	void createSimpleImageView(const VkDevice a_logicalDevice, const VkImage a_image, const VkFormat a_format, const VkImageAspectFlags a_aspectFlags, VkImageView& a_imgView);
}