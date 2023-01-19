#pragma once

#include "vulkan/vulkan.h"
#include "vk_globals.h"

namespace Vulkan
{
	class IDisplayer;

	void displayDeviceproperties(const VkPhysicalDeviceProperties& a_deviceProperties, IDisplayer& a_displayer);
	void displayDeviceQueuesproperties(const std::vector<VkQueueFamilyProperties>& a_queueFamilies, IDisplayer& a_displayer);
	void displayDeviceMemoryProperties(const VkPhysicalDeviceMemoryProperties& a_memPops, IDisplayer& a_displayer);
	void displayDeviceFeatures(const VkPhysicalDeviceFeatures& a_features, IDisplayer& a_displayer);
	void displayDeviceFormats(const std::vector<FormatProperty>& a_format, IDisplayer& a_displayer);
	void displayDeviceFormats(const SwapchainCapabilities& a_swapChain, IDisplayer& a_displayer);
}