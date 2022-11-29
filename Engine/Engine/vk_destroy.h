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
<<<<<<< HEAD
	/*@brief destroy vulkan instance*/
	void destroyVulkanInstance(VkInstance& a_vkInstance);
	/*@brief destroy vulkan device*/
	void destroyVulkanDevice(Device& a_device);
=======
	void destroyBuffer(VkDevice a_logicalDevice, Buffer& a_toDestroy);
>>>>>>> a597d2f6d4acdf8406486f7f9bbdfd6cc68f8272
}