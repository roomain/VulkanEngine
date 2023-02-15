#pragma once

#include "vulkan/vulkan.h"
#include "vk_globals.h"

namespace Vulkan
{
	class IDataDisplayer;

	void displayDeviceproperties(const VkPhysicalDeviceProperties& a_deviceProperties, IDataDisplayer& a_displayer);
	void displayDeviceQueuesproperties(const std::vector<VkQueueFamilyProperties>& a_queueFamilies, IDataDisplayer& a_displayer);
	void displayDeviceMemoryProperties(const VkPhysicalDeviceMemoryProperties& a_memPops, IDataDisplayer& a_displayer);
	void displayDeviceFeatures(const VkPhysicalDeviceFeatures& a_features, IDataDisplayer& a_displayer);
	void displayDeviceFormats(const std::vector<FormatProperty>& a_format, IDataDisplayer& a_displayer);
	void displayDeviceFormats(const SwapchainCapabilities& a_swapChain, IDataDisplayer& a_displayer);
}