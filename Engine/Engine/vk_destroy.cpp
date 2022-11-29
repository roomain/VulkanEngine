#include "pch.h"
#include "vk_destroy.h"

namespace Vulkan
{
	void destroyBaseImage(VkDevice a_logicalDevice, BaseImage& a_toDestroy)
	{
		if(a_toDestroy.imageView != VK_NULL_HANDLE)
			vkDestroyImageView(a_logicalDevice, a_toDestroy.imageView,nullptr);


		if (a_toDestroy.image != VK_NULL_HANDLE)
			vkDestroyImage(a_logicalDevice, a_toDestroy.image, nullptr);
	}

	void destroyImage(VkDevice a_logicalDevice, Image& a_toDestroy)
	{
		destroyBaseImage(a_logicalDevice, a_toDestroy);
		vkFreeMemory(a_logicalDevice, a_toDestroy.memory, nullptr);
	}

	void destroyImagePool(VkDevice a_logicalDevice, ImagePool& a_toDestroy)
	{
		for(auto& image : a_toDestroy.images)
			destroyBaseImage(a_logicalDevice, image);

		vkFreeMemory(a_logicalDevice, a_toDestroy.memory, nullptr);
	}

<<<<<<< HEAD

	void destroyVulkanInstance(VkInstance& a_vkInstance)
	{
		vkDestroyInstance(a_vkInstance, nullptr);
	}

	void destroyVulkanDevice(Device& a_device)
	{
		vkDestroyDevice(a_device.logicalDevice, nullptr);
	}

=======
	void destroyBuffer(VkDevice a_logicalDevice, Buffer& a_toDestroy)
	{
		vkDestroyBuffer(a_logicalDevice, a_toDestroy.buffer, nullptr);
		vkFreeMemory(a_logicalDevice, a_toDestroy.memory, nullptr);
	}
>>>>>>> a597d2f6d4acdf8406486f7f9bbdfd6cc68f8272
}