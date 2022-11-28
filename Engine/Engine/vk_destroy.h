#pragma once
#include "vulkan/vulkan.h"

namespace Vulkan
{
	struct BaseImage;
	struct Image;
	struct ImagePool;
	struct Buffer;

	void destroyBaseImage(VkDevice a_logicalDevice, BaseImage& a_toDestroy);
	void destroyImage(VkDevice a_logicalDevice, Image& a_toDestroy);
	void destroyImagePool(VkDevice a_logicalDevice, ImagePool& a_toDestroy);
	void destroyBuffer(VkDevice a_logicalDevice, Buffer& a_toDestroy);
}