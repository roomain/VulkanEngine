#pragma once
#include "vulkan/vulkan.h"
#include <string>
#include <vector>

namespace Vulkan
{
	struct Device;
	struct RendererQueuesConfiguration;
	struct VulkanConfiguration;

	void createVulkanInstance(const VulkanConfiguration& a_conf, VkInstance& a_vkInstance);

	void createVulkanDevice(const RendererQueuesConfiguration& a_queueConf, const std::vector<std::string>& a_deviceExt, Device& a_device);
}