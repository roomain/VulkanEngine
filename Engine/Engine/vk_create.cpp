#include "pch.h"
#include "vk_create.h"
#include "vk_struct_initializers.h"
#include "vk_ext_struct.h"

namespace Vulkan
{
	void createVulkanDevice(VkInstance& a_vkInstance, const RendererQueuesConfiguration& a_queueConf, Device& _device)
	{
		// create queues create info for the device
		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		for (const auto& conf : a_queueConf.vQueueConf)
		{
			auto createInfo = Initializers::queueCreateInfo();
			createInfo.queueCount = 1;
			createInfo.queueFamilyIndex = conf.index;
			queueCreateInfos.emplace_back(std::move(createInfo));
		}

		// info for create logical device
		VkDeviceCreateInfo deviceCreateInfo = Initializers::deviceCreateInfo();
		deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());		// Number of Queue Create Infos
		deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();								// List of queue create infos so device can create required queues
		//deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());	// Number of enabled logical device extensions
		//deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions.data();
	}
}