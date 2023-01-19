#pragma once
#include <vector>
#include <string>
#include "vulkan/vulkan.h"
#include "vk_globals.h"


namespace Vulkan
{

	struct DeviceQueuesConfiguration;


	/*@brief check if physical device support extensions*/
	[[nodiscard]] bool checkPhysicalDeviceExtension(VkPhysicalDevice a_physicalDevice, const std::vector<std::string>& a_extension);

	/*@brief check if physical device support queues configuration*/
	bool checkPhysicalDeviceQueues(VkPhysicalDevice a_physicalDevice, const VkSurfaceKHR a_surface, DeviceQueuesConfiguration& a_queueConf);

}