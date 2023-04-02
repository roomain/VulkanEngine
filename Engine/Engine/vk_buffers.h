#pragma once

#include "vulkan/vulkan.h"
#include <vector>

/*@brief utility extension structures*/
namespace Vulkan
{
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