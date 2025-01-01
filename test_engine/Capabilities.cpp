#include <iostream>
#include <string>
#include "Capabilities.h"
#include "VulkanContext.h"
#include "vulkan_enum_to_string.h"

std::string toVersion(const uint32_t a_version)
{
	return  std::to_string(a_version >> 22) + "." + std::to_string((a_version >> 12) & 0x3ff) + "." + std::to_string(a_version & 0xfff);
}

void displayCapabilities(const std::shared_ptr<VulkanCapabilities>& a_capabilities)
{
	std::cout << "Instance Extensions:";
	for (auto ext = VulkanCapabilities::extensionBegin(); ext != VulkanCapabilities::extensionEnd(); ++ext)
	{
		std::cout << "\n\t" << ext->extensionName << " version: " << toVersion(ext->specVersion);
	}

	std::cout << "\n\nInstance layers:";
	for (auto lay = VulkanCapabilities::layerBegin(); lay != VulkanCapabilities::layerEnd(); ++lay)
	{
		std::cout << "\n\t" << lay->layerName << " version: " << toVersion(lay->implementationVersion);
		std::cout << "\n\t\t" << lay->description << " version: " << toVersion(lay->specVersion);
	}

	std::cout << "\n\nDevices:";
	for (auto dev = a_capabilities->deviceBegin(); dev != a_capabilities->deviceEnd(); ++dev)
	{
		VulkanDeviceInfo info = dev->deviceInfo();
		std::cout << "\n\t" << info.deviceType << " API version: " << toVersion(info.apiVersion);
		std::cout << "\n\t\t" << info.name << " Driver version: " << toVersion(info.driverVersion);

		std::cout << "\nDevice Extensions:";
		for (auto ext : dev->m_extensions)
		{
			std::cout << "\n\t\t" << ext.extensionName << " version: " << toVersion(ext.specVersion);
		}

		std::cout << "\nDevice layers:";
		for (auto lay : dev->m_layersProperties)
		{
			std::cout << "\n\t\t" << lay.layerName << " version: " << toVersion(lay.implementationVersion);
			std::cout << "\n\t\t\t" << lay.description << " version: " << toVersion(lay.specVersion);
		}

		std::cout << "\n\nDevice queues:";
		for (auto queue : dev->m_queueFamilies)
		{			
			std::cout << "\n\t\tFlags: " << Flag<VkQueueFlagBits>::to_string(queue.queueFlags);
			std::cout << "\n\t\tCount" << queue.queueCount;
			std::cout << "\n";
		}
	}
	std::cout << "\n";
}