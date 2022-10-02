#pragma once
#include <iostream>
#include <vector>
#include "vulkan/vulkan.h"
#include "vk_globals.h"


namespace Vulkan
{
	struct Device;
	struct SwapchainCapabilities;
	struct FormatProperty;
	struct EngineDeviceCapabilities;
	class IDisplayer;

	void ENGINE_EXPORT getQueueFamiliesProperties(const Device& a_device, std::vector<VkQueueFamilyProperties>& a_familiesProperties);
	void ENGINE_EXPORT getFormatsProperties(const Device& a_device, std::vector<FormatProperty>& a_formatsProperties);
	void ENGINE_EXPORT getSwapChainCapabilities(const Device& a_device, const VkSurfaceKHR& a_surface, SwapchainCapabilities& a_swapChainCap);
	void ENGINE_EXPORT getDeviceCapabilities(const Device& a_device, EngineDeviceCapabilities& a_capabilities);
	void ENGINE_EXPORT enumerateDevices(VkInstance a_vulkan, std::vector<Device>& a_devices);

	void ENGINE_EXPORT getInstanceLayerProps(std::vector<VkLayerProperties>& a_properties);
	void ENGINE_EXPORT getInstanceExtProps(std::vector<VkExtensionProperties>& a_properties);
	//--------------------------------------------------------------------------------------------------------------------------
	void ENGINE_EXPORT displayInstanceLayerProps(IDisplayer& a_displayer);
	void ENGINE_EXPORT displayInstanceExtensionProps(IDisplayer& a_displayer);

	bool ENGINE_EXPORT checkInstanceLayerProps(const std::vector<const char*>& a_properties);
	bool ENGINE_EXPORT checkInstanceExtensionProps(const std::vector<const char*>& a_properties, bool& a_hasDebugExt);

	void ENGINE_EXPORT displayVulkanCapabilities(VkInstance a_vulkan, IDisplayer& a_displayer);
	void ENGINE_EXPORT displayDeviceCapabilities(VkPhysicalDevice a_physicalDevice, IDisplayer& a_displayer);

	void ENGINE_EXPORT displayDeviceLimits(const VkPhysicalDeviceLimits& a_limits, IDisplayer& a_displayer);
	void ENGINE_EXPORT displayDeviceSparseProps(const VkPhysicalDeviceSparseProperties& a_props, IDisplayer& a_displayer);
	void ENGINE_EXPORT displayDeviceCapabilities(const EngineDeviceCapabilities& a_capabilities, IDisplayer& a_displayer);
	// TODO
}