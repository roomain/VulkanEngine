#pragma once
#include "vulkan/vulkan.h"
#include <vector>
#include <string>
#include "vk_globals.h"


namespace Vulkan
{
	/*@brief short device info*/
	struct DeviceInfo
	{
		std::string deviceName;	/*!< device name*/
		std::string deviceType;	/*!< device type*/
	};

	void ENGINE_EXPORT enumerateDevicesInfo(VkInstance a_vulkan, std::vector<DeviceInfo>& a_info);

}