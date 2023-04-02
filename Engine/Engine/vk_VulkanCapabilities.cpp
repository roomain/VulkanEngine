#include "pch.h"
#include "vk_VulkanCapabilities.h"
#include "vk_WindowSystemProxy.h"


namespace Vulkan
{
	VK_VulkanCapabilities VK_VulkanCapabilities::m_instance;

	VK_VulkanCapabilities::VK_VulkanCapabilities() :m_instanceCapabilities{}
	{
		//
	}

	VK_VulkanCapabilities& VK_VulkanCapabilities::instance()
	{
		return m_instance;
	}

	uint32_t VK_VulkanCapabilities::enumerateDeviceCapabilities(const VkInstance a_instance)
	{
		uint32_t devCount = 0;
		vkEnumeratePhysicalDevices(a_instance, &devCount, nullptr);
		std::vector<VkPhysicalDevice> vDevices(devCount);
		vkEnumeratePhysicalDevices(a_instance, &devCount, vDevices.data());
		for (const auto devHandle : vDevices)
			m_vDeviceCapabilities.emplace_back(VK_DeviceCapabilities{ devHandle });

		return devCount;
	}
	
	void VK_VulkanCapabilities::display(IDataDisplayer& a_displayer)const
	{
		m_instanceCapabilities.display(a_displayer);
		for (const auto& devCap : m_vDeviceCapabilities)
			devCap.display(a_displayer);
	}

	void VK_VulkanCapabilities::searchCompatibleDevice(const VulkanConfiguration& a_conf, const std::shared_ptr<VK_WindowSystemProxy>& a_pWinProxy, std::vector<DeviceInfo>& a_vDevice)
	{
		uint32_t iDeviceIndex = 0;
		// check if queue support surface for graphical: vkGetPhysicalDeviceSurfaceSupportKHR (QueueConfiguration::presentationSupport)
		for (auto& devCap : m_vDeviceCapabilities)
		{
			devCap.getSwapChainCapabilities(a_pWinProxy->surface());
			DeviceQueuesConfiguration tempQueueConf = a_conf.queues;
			for (auto& queueConf : tempQueueConf.vQueueConf)
			{
				int iFamilyIndex = 0;
				for (const auto& queueCap : devCap.m_queueFamilies)
				{
					if (queueCap.queueCount > 0)
					{
						if (queueConf.type == (queueConf.type & queueCap.queueFlags))
						{
							queueConf.index = iFamilyIndex;
							if (a_pWinProxy)
							{
								VkBool32 presentationSupport = VK_FALSE;
								VK_CHECK(vkGetPhysicalDeviceSurfaceSupportKHR(devCap.m_physicalDevice, iFamilyIndex, a_pWinProxy->surface(), &presentationSupport))
									queueConf.presentationSupport = presentationSupport == VK_TRUE;
							}
						}
					}
					++iFamilyIndex;
				}
			}

			if (tempQueueConf.isValid())
				a_vDevice.emplace_back(iDeviceIndex, devCap.m_deviceProperties.deviceName, 
					to_string(devCap.m_deviceProperties.deviceType), devCap.m_deviceProperties.apiVersion, devCap.m_deviceProperties.driverVersion);

			++iDeviceIndex;
		}
	}
}