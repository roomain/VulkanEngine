#pragma once

#include "vulkan/vulkan.h"
#include <vector>
#include <algorithm>

/*@brief utility extension structures*/
namespace Vulkan
{
	/*@brief represents vulkan device*/
	struct Device
	{
		VkPhysicalDevice physical = VK_NULL_HANDLE;		/*!< physical device*/
		VkDevice logicalDevice = VK_NULL_HANDLE;		/*!< logical device*/
	};
	
	/*@brief repesents an image without memory*/
	struct BaseImage
	{
		VkImage image = VK_NULL_HANDLE;
		VkImageView imageView = VK_NULL_HANDLE;
	};

	/*@brief image with memory*/
	struct Image : BaseImage
	{
		VkDeviceMemory memory = VK_NULL_HANDLE;
	};

	/*@brief a pool of image with same format and size*/
	struct ImagePool
	{
		VkDeviceMemory memory = VK_NULL_HANDLE;			/*!< memory containing all images*/
		std::vector<BaseImage> images;
	};

	/*@brief represents a buffer*/
	struct Buffer
	{
		VkBuffer buffer = VK_NULL_HANDLE;
		VkDeviceMemory memory = VK_NULL_HANDLE;
	};

	//----------------------------------------------------------------------------
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
	struct EngineDeviceCapabilities
	{
		SwapchainCapabilities swapChanCapabilities;			/*!< device swapchain capabilities*/
		VkPhysicalDeviceProperties deviceProperties;		/*!< porperties of the device*/
		VkPhysicalDeviceFeatures deviceFeatures;			/*!< features supported by device*/
		VkPhysicalDeviceMemoryProperties memoryProperties;	/*!< device memory properties*/
		std::vector<FormatProperty> formatsProperties;		/*!< properties for each supported format*/
		std::vector<VkQueueFamilyProperties> queueFamilies;	/*!< properties of queue families*/
		// TODO
	};

	/*@brief Queue configuration*/
	struct QueueConfiguration
	{
		VkQueueFlags type;		/*!< queue type*/
		int index = -1;			/*!< queue location index*/
	};

	//----------------------------------------------------------------------------
	/*@brief Queues configuration corresponding to the needs*/
	struct RendererQueuesConfiguration
	{
		std::vector<QueueConfiguration> vQueueConf;

		inline void reset()
		{
			for (auto& conf : vQueueConf)
				conf.index = -1;
		}

		inline bool isValid()const noexcept
		{
			return std::all_of(vQueueConf.begin(), vQueueConf.end(), [](const QueueConfiguration& a_conf) {return a_conf.index >= 0; });
		}
	};

}