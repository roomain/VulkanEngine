#pragma once
#include "vulkan/vulkan.h"
#include <vector>

namespace Vulkan
{
	struct Device;
	struct SwapchainCapabilities;
	struct FormatProperty;
	struct EngineDeviceCapabilities;

	void getInstanceLayerProps(std::vector<VkLayerProperties>& a_properties);
	void getInstanceExtProps(std::vector<VkExtensionProperties>& a_properties);
	void getQueueFamiliesProperties(const Device& a_device, std::vector<VkQueueFamilyProperties>& a_familiesProperties);
	void getFormatsProperties(const Device& a_device, std::vector<FormatProperty>& a_formatsProperties);
	void getSwapChainCapabilities(const Device& a_device, const VkSurfaceKHR& a_surface, SwapchainCapabilities& a_swapChainCap);
	void getDeviceCapabilities(const Device& a_device, EngineDeviceCapabilities& a_capabilities);
}