#pragma once

#include <vector>
#include "vulkan/vulkan.h"

/*@brief utility extension structures*/
namespace Vulkan
{
	/*@brief get Instance capabilities*/
	struct InstanceCapabilities
	{
		std::vector<VkLayerProperties> layerPops;			/*!< layer properties*/
		std::vector<VkExtensionProperties> extensionProps;	/*!< extension properties*/
	};


	/*@brief Swapchain capabilities*/
	struct SwapchainCapabilities
	{
		VkSurfaceCapabilitiesKHR surfaceCapabilities;		/*!< surface properties eg image size / extent*/
		std::vector<VkSurfaceFormatKHR> supportedFormats;	/*!< supported image formats eg RGBA and size of each color*/
		std::vector<VkPresentModeKHR> supportedModes;		/*!< supported presentation modes*/
	};

	/*@brief image format properties*/
	struct FormatProperty
	{
		VkFormat format;				/*!< an image format*/
		VkFormatProperties properties;	/*!< physical device properties for the associated format*/
	};

	/*@brief current device capabilities*/
	struct DeviceCapabilities
	{
		VkPhysicalDevice physicalDevice;					/*!< handle to physical device*/
		SwapchainCapabilities swapChanCapabilities;			/*!< device swapchain capabilities*/
		VkPhysicalDeviceProperties deviceProperties;		/*!< porperties of the device*/
		VkPhysicalDeviceFeatures deviceFeatures;			/*!< features supported by device*/
		VkPhysicalDeviceMemoryProperties memoryProperties;	/*!< device memory properties*/
		std::vector<VkExtensionProperties> extensions;		/*!< device extensions*/
		std::vector<FormatProperty> formatsProperties;		/*!< properties for each supported format*/
		std::vector<VkQueueFamilyProperties> queueFamilies;	/*!< properties of queue families*/
	};
}