#pragma once

#include "vulkan/vulkan.h"
#include <vector>
#include <algorithm>

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

	/*@brief represents a buffer*/
	struct Buffer
	{
		VkBuffer buffer = VK_NULL_HANDLE;
		VkDeviceMemory memory = VK_NULL_HANDLE;
	};

	/*@brief represents a buffer pool*/
	struct BufferPool
	{
		std::vector<VkBuffer> vbuffer;
		VkDeviceMemory memory = VK_NULL_HANDLE;
	};
}