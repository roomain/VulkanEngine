#include "pch.h"


namespace Vulkan
{

	bool checkPhysicalDeviceExtension(VkPhysicalDevice a_physicalDevice, const std::vector<std::string>& a_extension)
	{
		std::vector<VkExtensionProperties> extensions;
		getDeviceExtensions(a_physicalDevice, extensions);
		return std::all_of(a_extension.begin(), a_extension.end(), [&](const auto& name)
			{
				return extensions.end() != std::find_if(extensions.begin(), extensions.end(), [&](auto prop)
					{
						return name.compare(prop.extensionName) == 0;
					});
			});
	}

	bool checkPhysicalDeviceQueues(VkPhysicalDevice a_physicalDevice, const VkSurfaceKHR a_surface, DeviceQueuesConfiguration& a_queueConf)
	{
		getDeviceQueues(a_physicalDevice, a_surface, a_queueConf);
		return a_queueConf.isValid();
	}
}