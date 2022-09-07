#include "pch.h"
#include "vk_propFun.h"
#include "vk_ext_struct.h"
#include "IDisplayer.h"

namespace Vulkan
{
	void getQueueFamiliesProperties(const Device& a_device, std::vector<VkQueueFamilyProperties>& a_familiesProperties)
	{
		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(a_device.physical, &queueFamilyCount, nullptr);
		a_familiesProperties.resize(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(a_device.physical, &queueFamilyCount, a_familiesProperties.data());
	}

	void getFormatsProperties(const Device& a_device, std::vector<FormatProperty>& a_formatsProperties)
	{
		for (int iterFormat = VK_FORMAT_R4G4_UNORM_PACK8; iterFormat < VK_FORMAT_MAX_ENUM; ++iterFormat)
		{
			FormatProperty formatProp;
			vkGetPhysicalDeviceFormatProperties(a_device.physical, static_cast<VkFormat>(iterFormat), &formatProp.properties);
			a_formatsProperties.push_back(formatProp);
		}
	}

	void getSwapChainCapabilities(const Device& a_device, const VkSurfaceKHR& a_surface, SwapchainCapabilities& a_swapChainCap)
	{
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(a_device.physical, a_surface, &a_swapChainCap.surfaceCapabilities);

		uint32_t formatCount = 0;
		vkGetPhysicalDeviceSurfaceFormatsKHR(a_device.physical, a_surface, &formatCount, nullptr);
		if(formatCount > 0)
		{
			a_swapChainCap.supportedFormats.resize(static_cast<int>(formatCount));
			vkGetPhysicalDeviceSurfaceFormatsKHR(a_device.physical, a_surface, &formatCount, a_swapChainCap.supportedFormats.data());
		}

		uint32_t presentCount = 0;
		vkGetPhysicalDeviceSurfacePresentModesKHR(a_device.physical, a_surface, &presentCount, nullptr);
		if(presentCount > 0)
		{
			a_swapChainCap.supportedModes.resize(static_cast<int>(presentCount));
			vkGetPhysicalDeviceSurfacePresentModesKHR(a_device.physical, a_surface, &presentCount, a_swapChainCap.supportedModes.data());
		}
	}

	void getDeviceCapabilities(const Device& a_device, EngineDeviceCapabilities& a_capabilities)
	{
		vkGetPhysicalDeviceProperties(a_device.physical, &a_capabilities.deviceProperties);
		vkGetPhysicalDeviceFeatures(a_device.physical, &a_capabilities.deviceFeatures);
		vkGetPhysicalDeviceMemoryProperties(a_device.physical, &a_capabilities.memoryProperties);		
		getSwapChainCapabilities(a_device, a_capabilities.swapChanCapabilities);
		getFormatsProperties(a_device, a_capabilities.formatsProperties);
		getQueueFamiliesProperties(a_device, a_capabilities.queueFamilies);
	}

	void displayDeviceCapabilities(const EngineDeviceCapabilities& a_capabilities, IDisplayer& a_displayer)
	{
		// TODO
	}
}