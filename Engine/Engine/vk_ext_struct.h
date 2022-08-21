#pragma once

#include "vulkan/vulkan.h"
#include <vector>

/*@brief utility extension structures*/
namespace Vulkan
{
	/*@brief represents vulkan device*/
	struct Device
	{
		VkPhysicalDevice physical;	/*!< physical device*/
		VkDevice logicalDevice;		/*!< logical device*/
	};
	
	/*@brief repesents an image without memory*/
	struct BaseImage
	{
		VkImage image;
		VkImageView imageView;
	};

	/*@brief image with memory*/
	struct Image : BaseImage
	{
		VkDeviceMemory memory;
	};

	/*@brief a pool of image with same format and size*/
	struct ImagePool
	{
		VkDeviceMemory memory;			/*!< memory containing all images*/
		std::vector<BaseImage> images;
	};

	/*@brief represents a buffer*/
	struct Buffer
	{
		VkBuffer buffer;
		VkDeviceMemory memory;
	};

	//----------------------------------------------------------------------------
	/*@brief Swapchain capabilities*/
	struct SwapchainCapabilities
	{
		VkSurfaceCapabilitiesKHR surfaceCapabilities;		/*!< surface properties eg image size / extent*/
		std::vector<VkSurfaceFormatKHR> supportedFormats;	/*!< supported image formats eg RGBA and size of each color*/
		std::vector<VkPresentModeKHR> supportedModes;		/*!< supportes presentation modes*/
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

	//----------------------------------------------------------------------------
	/*@brief Queues configuration corresponding to the needs*/
	struct QueuesConfiguration
	{
		int queuesFamily_graphics = -1;		/*!< index of a graphics family*/
		int queuesFamily_presentation = -1;	/*!< index of presentation family*/

		inline bool isValid()const noexcept
		{
			return (queuesFamily_graphics >= 0) && (queuesFamily_presentation >= 0);
		}
	};

}