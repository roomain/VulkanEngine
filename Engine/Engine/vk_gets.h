#pragma once
#include "vulkan/vulkan.h"
#include <vector>

namespace Vulkan
{
	struct Device;
	struct SwapchainCapabilities;
	struct FormatProperty;
	struct EngineDeviceCapabilities;
	struct RendererQueuesConfiguration;

	void getInstanceLayerProps(std::vector<VkLayerProperties>& a_properties);
	void getInstanceExtProps(std::vector<VkExtensionProperties>& a_properties);
	void getQueueFamiliesProperties(const VkPhysicalDevice& a_device, std::vector<VkQueueFamilyProperties>& a_familiesProperties);
	void getFormatsProperties(const VkPhysicalDevice& a_device, std::vector<FormatProperty>& a_formatsProperties);
	void getDeviceExtensions(const VkPhysicalDevice& a_device, std::vector<VkExtensionProperties>& a_extensions);
	void getSwapChainCapabilities(const Device& a_device, const VkSurfaceKHR& a_surface, SwapchainCapabilities& a_swapChainCap);
	void getDeviceCapabilities(const Device& a_device, EngineDeviceCapabilities& a_capabilities);
	void getDeviceQueues(const VkPhysicalDevice& a_physicalDevice, RendererQueuesConfiguration& a_queueConf);
	//---------------------------------------------------------------------------------------------------------------------------------------------------------

	[[nodiscard]] VkFormat getSupportedFormat(const Device& a_device, const std::vector<VkFormat>& a_formats, const VkImageTiling a_tiling, const VkFormatFeatureFlags a_featureFlag);
	[[nodiscard]] VkFormat getSupportedFormat(const Device& a_device, std::vector<VkFormat>&& a_formats, VkImageTiling&& a_tiling, VkFormatFeatureFlags&& a_featureFlag);
	[[nodiscard]] uint32_t getMemoryTypeIndex(const VkPhysicalDeviceMemoryProperties& a_memProperties, uint32_t a_memTypeBits, VkMemoryPropertyFlags a_flags);

	[[nodiscard]] VkSurfaceFormatKHR getBestSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& a_vformats);
	[[nodiscard]] VkPresentModeKHR getBestPresentationMode(const std::vector<VkPresentModeKHR>& a_vPresentationModes);
}