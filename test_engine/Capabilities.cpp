#include <iostream>
#include "Capabilities.h"
#include "VulkanContext.h"

void displayCapabilities()
{
	VulkanCapabilities& capabilities = VulkanContext::getCapabilities();
	std::cout << "Instance Extensions:";
	for (auto ext = capabilities.extensionBegin(); ext != capabilities.extensionEnd(); ++ext)
	{
		std::cout << "\n\t" << ext->extensionName << " version: " << ext->specVersion;
	}

	std::cout << "\n\nInstance layers:";
	for (auto lay = capabilities.layerBegin(); lay != capabilities.layerEnd(); ++lay)
	{
		std::cout << "\n\t" << lay->layerName << " version: " << lay->implementationVersion;
		std::cout << "\n\t\t" << lay->description << " version: " << lay->specVersion;
	}

	std::cout << "\n\nDevices:";
	for (auto dev = capabilities.deviceBegin(); dev != capabilities.deviceEnd(); ++dev)
	{
		VulkanDeviceInfo info = dev->deviceInfo();
		std::cout << "\n\t" << info.deviceType << " API version: " << info.apiVersion;
		std::cout << "\n\t\t" << info.name << " Driver version: " << info.driverVersion;
	}

}