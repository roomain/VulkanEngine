#include "pch.h"
#include "vk_enumerate.h"
#include "vk_enum_to_string.h"

namespace Vulkan
{
	void enumerateDevicesInfo(VkInstance a_vulkan, std::vector<DeviceInfo>& a_info)
	{
		uint32_t uiDeviceCount = 0;
		VK_CHECK(vkEnumeratePhysicalDevices(a_vulkan, &uiDeviceCount, nullptr));
		if (uiDeviceCount > 0)
		{
			std::vector<VkPhysicalDevice> physicalDevices(static_cast<size_t>(uiDeviceCount));
			VK_CHECK(vkEnumeratePhysicalDevices(a_vulkan, &uiDeviceCount, physicalDevices.data()));

			for (auto dev : physicalDevices)
			{
				VkPhysicalDeviceProperties devProp;
				vkGetPhysicalDeviceProperties(dev, &devProp);
				a_info.emplace_back(devProp.deviceName, to_string(devProp.deviceType));
			}
		}
	}
}