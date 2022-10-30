#pragma once
#include "vulkan/vulkan.h"

namespace Vulkan
{
	struct Device;
	struct RendererQueuesConfiguration;
	
	void createVulkanDevice(VkInstance& a_vkInstance, const RendererQueuesConfiguration& a_queueConf, Device& _device);
}