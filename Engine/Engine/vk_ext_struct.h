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
	
	/*@brief repesents an image*/
	struct Image
	{
		VkImage image;
		VkImageView imageView;
	};

	/*@brief represents a buffer*/
	struct Buffer
	{
		VkBuffer buffer;
		VkDeviceMemory memory;
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

	/*@brief Swapchain capabilities*/
	struct SwapchainCapabilities
	{
		VkSurfaceCapabilitiesKHR surfaceCapabilities;		/*!< surface properties eg image size / extent*/
		std::vector<VkSurfaceFormatKHR> supportedFormats;	/*!< supported image formats eg RGBA and size of each color*/
		std::vector<VkPresentModeKHR> supportedModes;		/*!< supportes presentation modes*/
	};
}