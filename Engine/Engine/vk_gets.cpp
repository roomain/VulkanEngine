#include "pch.h"
#include "vk_ext_struct.h"

namespace Vulkan
{

	void getInstanceLayerProps(std::vector<VkLayerProperties>& a_properties)
	{
		uint32_t propCount = 0;
		vkEnumerateInstanceLayerProperties(&propCount, nullptr);
		a_properties.resize(propCount);
		vkEnumerateInstanceLayerProperties(&propCount, a_properties.data());

	}

	void getInstanceExtProps(std::vector<VkExtensionProperties>& a_properties)
	{
		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
		a_properties.resize(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, a_properties.data());
	}

	void getQueueFamiliesProperties(const VkPhysicalDevice& a_device, std::vector<VkQueueFamilyProperties>& a_familiesProperties)
	{
		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(a_device, &queueFamilyCount, nullptr);
		a_familiesProperties.resize(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(a_device, &queueFamilyCount, a_familiesProperties.data());
	}

	void getFormatsProperties(const VkPhysicalDevice& a_device, std::vector<FormatProperty>& a_formatsProperties)
	{
		for (int iterFormat = VK_FORMAT_R4G4_UNORM_PACK8; iterFormat < VK_FORMAT_MAX_ENUM; ++iterFormat)
		{
			FormatProperty formatProp{ .format = static_cast<VkFormat>(iterFormat) };
			vkGetPhysicalDeviceFormatProperties(a_device, static_cast<VkFormat>(iterFormat), &formatProp.properties);
			a_formatsProperties.push_back(formatProp);
		}
	}

	void getDeviceExtensions(const VkPhysicalDevice& a_device, std::vector<VkExtensionProperties>& a_extensions)
	{
		uint32_t extensionCount = 0;
		vkEnumerateDeviceExtensionProperties(a_device, nullptr, &extensionCount, nullptr);
		a_extensions.resize(extensionCount);
		vkEnumerateDeviceExtensionProperties(a_device, nullptr, &extensionCount, a_extensions.data());
	}

	void getSwapChainCapabilities(const Device& a_device, const VkSurfaceKHR& a_surface, SwapchainCapabilities& a_swapChainCap)
	{
		VK_CHECK(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(a_device.physical, a_surface, &a_swapChainCap.surfaceCapabilities));

		uint32_t formatCount = 0;
		VK_CHECK(vkGetPhysicalDeviceSurfaceFormatsKHR(a_device.physical, a_surface, &formatCount, nullptr));
		if (formatCount > 0)
		{
			a_swapChainCap.supportedFormats.resize(static_cast<int>(formatCount));
			VK_CHECK(vkGetPhysicalDeviceSurfaceFormatsKHR(a_device.physical, a_surface, &formatCount, a_swapChainCap.supportedFormats.data()));
		}

		uint32_t presentCount = 0;
		VK_CHECK(vkGetPhysicalDeviceSurfacePresentModesKHR(a_device.physical, a_surface, &presentCount, nullptr));
		if (presentCount > 0)
		{
			a_swapChainCap.supportedModes.resize(static_cast<int>(presentCount));
			VK_CHECK(vkGetPhysicalDeviceSurfacePresentModesKHR(a_device.physical, a_surface, &presentCount, a_swapChainCap.supportedModes.data()));
		}
	}

	void getDeviceCapabilities(const Device& a_device, EngineDeviceCapabilities& a_capabilities)
	{
		vkGetPhysicalDeviceProperties(a_device.physical, &a_capabilities.deviceProperties);
		vkGetPhysicalDeviceFeatures(a_device.physical, &a_capabilities.deviceFeatures);
		vkGetPhysicalDeviceMemoryProperties(a_device.physical, &a_capabilities.memoryProperties);
		getFormatsProperties(a_device.physical, a_capabilities.formatsProperties);
		getQueueFamiliesProperties(a_device.physical, a_capabilities.queueFamilies);
	}

	void getDeviceQueues(const VkPhysicalDevice& a_physicalDevice, RendererQueuesConfiguration& a_queueConf)
	{
		a_queueConf.reset();
		// get memory properties
		std::vector<VkQueueFamilyProperties> queuesProperties;
		getQueueFamiliesProperties(a_physicalDevice, queuesProperties);

		// check an feels queues
		int iFamilyIndex = 0;
		for (const auto& queueFamily : queuesProperties)
		{
			if (queueFamily.queueCount > 0)// at least on queue
			{
				for (auto& queueConf : a_queueConf.vQueueConf)
				{
					if (queueConf.type == (queueConf.type & queueFamily.queueFlags))
					{
						queueConf.index = iFamilyIndex;
						break;
					}
				}
			}
			++iFamilyIndex;
		}
	}

	//---------------------------------------------------------------------------------------------------------------------------------------------------------

	VkFormat getSupportedFormat(const Device& a_device, const std::vector<VkFormat>& a_formats, const VkImageTiling a_tiling, const VkFormatFeatureFlags a_featureFlag)
	{
		// Loop through options and find compatible one
		for (VkFormat format : a_formats)
		{
			// Get properties for give format on this device
			VkFormatProperties properties;
			vkGetPhysicalDeviceFormatProperties(a_device.physical, format, &properties);

			// Depending on tiling choice, need to check for different bit flag
			switch (a_tiling)
			{
			case VK_IMAGE_TILING_LINEAR:
				if ((properties.linearTilingFeatures & a_featureFlag) == a_featureFlag)
					return format;
				break;

			case VK_IMAGE_TILING_OPTIMAL:
				if ((properties.optimalTilingFeatures & a_featureFlag) == a_featureFlag)
					return format;
				break;

			default:
				break;
			}
		}

		throw VK_Exception("Failed to find a matching format!", std::source_location::current());
	}

	VkFormat getSupportedFormat(const Device& a_device, std::vector<VkFormat>&& a_formats, VkImageTiling&& a_tiling, VkFormatFeatureFlags&& a_featureFlag)
	{
		// Loop through options and find compatible one
		for (VkFormat format : a_formats)
		{
			// Get properties for give format on this device
			VkFormatProperties properties;
			vkGetPhysicalDeviceFormatProperties(a_device.physical, format, &properties);

			// Depending on tiling choice, need to check for different bit flag
			switch (a_tiling)
			{
			case VK_IMAGE_TILING_LINEAR:
				if ((properties.linearTilingFeatures & a_featureFlag) == a_featureFlag)
					return format;
				break;

			case VK_IMAGE_TILING_OPTIMAL:
				if ((properties.optimalTilingFeatures & a_featureFlag) == a_featureFlag)
					return format;
				break;

			default:
				break;
			}
		}
		throw VK_Exception("Failed to find a matching format!", std::source_location::current());
	}

	uint32_t getMemoryTypeIndex(const VkPhysicalDeviceMemoryProperties& a_memProperties, uint32_t a_memTypeBits, VkMemoryPropertyFlags a_flags)
	{
		for (uint32_t iIndex = 0; iIndex < a_memProperties.memoryTypeCount; iIndex++)
		{
			if ((a_memTypeBits & (1 << iIndex))														// Index of memory type must match corresponding bit in allowedTypes
				&& (a_memProperties.memoryTypes[iIndex].propertyFlags & a_flags) == a_flags)		// Desired property bit flags are part of memory type's property flags
			{
				// This memory type is valid, so return its index
				return iIndex;
			}
		}
		throw Vulkan::VK_Exception("Can't find Memory index.", std::source_location::current());
	}

	VkSurfaceFormatKHR getBestSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& a_vformats)
	{
		// If only 1 format available and is undefined, then this means ALL formats are available (no restrictions)
		if (a_vformats.size() == 1 && a_vformats[0].format == VK_FORMAT_UNDEFINED)
			return{ VK_FORMAT_R8G8B8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };

		// If restricted, search for optimal format
		auto iter = std::find_if(a_vformats.begin(), a_vformats.end(), [&](const auto& format)
			{
				return (format.format == VK_FORMAT_R8G8B8A8_UNORM || format.format == VK_FORMAT_B8G8R8A8_UNORM)
				&& format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
		});
		if(iter != a_vformats.end())
			return *iter;

		// If can't find optimal format, then just return first format
		return a_vformats[0];
	}

	VkPresentModeKHR getBestPresentationMode(const std::vector<VkPresentModeKHR>& a_vPresentationModes)
	{
		if (std::find(a_vPresentationModes.cbegin(), a_vPresentationModes.cend(), VK_PRESENT_MODE_MAILBOX_KHR) != a_vPresentationModes.cend())
			return VK_PRESENT_MODE_MAILBOX_KHR;

		return VK_PRESENT_MODE_FIFO_KHR;
	}
}