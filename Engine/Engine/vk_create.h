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

	/*@brief create vulkan instance from a configuration*/
	void createVulkanInstance(const VulkanConfiguration& a_conf, VkInstance& a_vkInstance);
	/*@brief destroy vulkan instance*/
	void destroyVulkanInstance(VkInstance& a_vkInstance);

	/*@brief create vulkan device from Queue configuration and device extension needed*/
	void createVulkanDevice(const RendererQueuesConfiguration& a_queueConf, const std::vector<std::string>& a_deviceExt, Device& a_device);
	/*@brief destroy vulkan device*/
	void destroyVulkanDevice(Device& a_device);

	/*@brief create swap chain from format and window proxy, retrieves images from created swap chain (destroy oldswapchain)*/
	void createSwapChain(const Device& a_device, VkSwapchainKHR& a_swapChain, VkSurfaceFormatKHR& a_surfaceFormat, std::unique_ptr<VK_WindowSystemProxy>&& a_windowProxy, std::vector<BaseImage>& a_images);
	/*@brief destroy swapchain and release linked image view*/
	void destroySwapChain(const Device& a_device, VkSwapchainKHR& a_swapChain, std::vector<BaseImage>& a_images);

	/*@brief create image*/
	void createSimpleImageView(const VkDevice a_logicalDevice, const VkImage a_image, const VkFormat a_format, const VkImageAspectFlags a_aspectFlags, VkImageView& a_imgView);
}