#pragma once

#include "vulkan/vulkan.h"
#include <vector>

/*@brief utility extension structures*/
namespace Vulkan
{
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

}