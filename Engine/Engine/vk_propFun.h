#pragma once
#include <iostream>
#include <vector>

struct VkQueueFamilyProperties;

namespace Vulkan
{
	struct Device;
	struct SwapchainCapabilities;
	struct FormatProperty;
	struct EngineDeviceCapabilities;

	void getQueueFamiliesProperties(const Device& a_device, std::vector<VkQueueFamilyProperties>& a_familiesProperties);
	void getFormatsProperties(const Device& a_device, std::vector<FormatProperty>& a_formatsProperties);
	void getSwapChainCapabilities(const Device& a_device, SwapchainCapabilities& a_swapChainCap);
	void getDeviceCapabilities(const Device& a_device, EngineDeviceCapabilities& a_capabilities);

	void displayDeviceCapabilities(const EngineDeviceCapabilities& a_capabilities, std::istream& a_stream);
	// TODO
}