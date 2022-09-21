#pragma once
#include <iostream>
#include <vector>
#include "vulkan/vulkan.h"


namespace Vulkan
{
	struct Device;
	struct SwapchainCapabilities;
	struct FormatProperty;
	struct EngineDeviceCapabilities;
	class IDisplayer;

	void getQueueFamiliesProperties(const Device& a_device, std::vector<VkQueueFamilyProperties>& a_familiesProperties);
	void getFormatsProperties(const Device& a_device, std::vector<FormatProperty>& a_formatsProperties);
	void getSwapChainCapabilities(const Device& a_device, const VkSurfaceKHR& a_surface, SwapchainCapabilities& a_swapChainCap);
	void getDeviceCapabilities(const Device& a_device, EngineDeviceCapabilities& a_capabilities);
	void enumerateDevices(VkInstance a_vulkan, std::vector<Device>& a_devices);
	//--------------------------------------------------------------------------------------------------------------------------
	void displayVulkanCapabilities(VkInstance a_vulkan, IDisplayer& a_displayer);
	void displayDeviceCapabilities(VkPhysicalDevice a_physicalDevice, IDisplayer& a_displayer);
	void displayDeviceLimits(const VkPhysicalDeviceLimits& a_limits, IDisplayer& a_displayer);
	void displayDeviceSparseProps(const VkPhysicalDeviceSparseProperties& a_props, IDisplayer& a_displayer);
	void displayDeviceCapabilities(const EngineDeviceCapabilities& a_capabilities, IDisplayer& a_displayer);
	// TODO
}