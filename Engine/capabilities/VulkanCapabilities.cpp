#include "pch.h"
#include "VulkanCapabilities.h"
#include "common/enumerate.h"
#include "VulkanInitializers.h"
#include "Vulkan_macros.h"
#include "parameters/VulkanParameter.h"
#include "common/string_utils.h"
#include "common/contains.h"


std::vector<VkExtensionProperties> VulkanCapabilities::m_instanceExt;
std::vector<VkLayerProperties> VulkanCapabilities::m_instanceLay;

void VulkanCapabilities::initInstanceExt()noexcept
{
	enumerate(&vkEnumerateInstanceExtensionProperties, m_instanceExt, nullptr);
}

void VulkanCapabilities::initInstanceLay()noexcept
{
	enumerate(&vkEnumerateInstanceLayerProperties, m_instanceLay);
}

VulkanCapabilities::VulkanCapabilities(VkInstance a_instance) : m_instance{ a_instance }
{
	std::vector<VkPhysicalDevice> vDevices;
	enumerate(&vkEnumeratePhysicalDevices, vDevices, m_instance);
	int index = 0;
	for (const auto& physicalDev : vDevices)
	{
		m_devices.emplace_back(VulkanDeviceCapabilities(index ,physicalDev));
		++index;
	}
}

VulkanCapabilities::Extension_const_iterator VulkanCapabilities::extensionBegin()noexcept
{
	if (m_instanceExt.empty())
		VulkanCapabilities::initInstanceExt();
	return m_instanceExt.cbegin();
}

VulkanCapabilities::Extension_const_iterator VulkanCapabilities::extensionEnd()noexcept
{
	if (m_instanceExt.empty())
		VulkanCapabilities::initInstanceExt();
	return m_instanceExt.cend();
}

VulkanCapabilities::Layer_const_iterator VulkanCapabilities::layerBegin()noexcept
{
	if (m_instanceLay.empty())
		VulkanCapabilities::initInstanceLay();
	return m_instanceLay.cbegin();
}

VulkanCapabilities::Layer_const_iterator VulkanCapabilities::layerEnd()noexcept
{
	if (m_instanceLay.empty())
		VulkanCapabilities::initInstanceLay();
	return m_instanceLay.cend();
}

VulkanCapabilities::Device_const_iterator VulkanCapabilities::deviceBegin()const noexcept
{
	return m_devices.cbegin();
}

VulkanCapabilities::Device_const_iterator VulkanCapabilities::deviceEnd()const noexcept
{
	return m_devices.cend();
}

void VulkanCapabilities::findDeviceCompatibleConfiguration(const VulkanDeviceParameter& a_parameters, VulkanDeviceConfMap& a_conf, VkSurfaceKHR a_surface)const
{	
	int deviceIndex = 0;
	for (const auto& deviceCap : m_devices)
	{
		// check layers
		if (!contains<VkLayerProperties>(deviceCap.layerBegin(), deviceCap.layerEnd(), a_parameters.layers,
			[](const std::string_view& a_search, const VkLayerProperties& a_layer)
			{
				return a_search.compare(a_layer.layerName) == 0;
			}))
			continue;

		// check extensions
		if (!contains<VkExtensionProperties>(deviceCap.extensionBegin(), deviceCap.extensionEnd(), a_parameters.extensions,
			[](const std::string_view& a_search, const VkExtensionProperties& a_extension)
			{
				return a_search.compare(a_extension.extensionName) == 0;
			}))
			continue;

		if (!deviceCap.isFeaturesAvailable(a_parameters.features))
			continue;

		VulkanDeviceQueuesConf queueConf;
		// contains number of available queue per family
		std::unordered_map<int, uint32_t> QueuesFamilyRemainQueues;
		int currentMissingQueueCount = 0;

		
		for (auto queueFamilyParam : a_parameters.queues)// need a copy
		{
			uint32_t queueFamilyIndex = 0;
			bool bPresentableOk = !queueFamilyParam.bPresentationAvailable;

			// search compatiblequeue
			for (auto iter = deviceCap.queueBegin(); iter != deviceCap.queueEnd() && (queueFamilyParam.count > 0); ++iter)
			{
				if ((iter->queueFlags & static_cast<VkQueueFlags>(queueFamilyParam.flags)) == static_cast<VkQueueFlags>(queueFamilyParam.flags))
				{
					if (a_surface && queueFamilyParam.bPresentationAvailable)
					{
						VkBool32 supported = false;
						VK_CHECK_LOG(vkGetPhysicalDeviceSurfaceSupportKHR(deviceCap.physicalDevice(), queueFamilyIndex, a_surface, &supported))
						if (!supported)
						{
							queueFamilyIndex++;
							continue;
						}
						bPresentableOk = true;
					}


					uint32_t minKeep = 0;
					if (auto iterQueue = QueuesFamilyRemainQueues.find(queueFamilyIndex); iterQueue != QueuesFamilyRemainQueues.end())
					{
						minKeep = std::min(iterQueue->second, queueFamilyParam.count);
						iterQueue->second -= minKeep;
						queueFamilyParam.count -= minKeep;
					}
					else
					{
						minKeep = std::min(iter->queueCount, queueFamilyParam.count);
						QueuesFamilyRemainQueues[queueFamilyIndex] = iter->queueCount - minKeep;
						queueFamilyParam.count -= minKeep;
					}

					queueConf.baseCreateInfo.emplace_back(
						VkDeviceQueueCreateInfo{
							.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
							.pNext = nullptr,
							.flags = static_cast<VkQueueFlags>(queueFamilyParam.flags),
							.queueFamilyIndex = queueFamilyIndex,
							.queueCount = minKeep,
							.pQueuePriorities = nullptr
						}
					);
					
					for (uint32_t index = 0; index < minKeep; ++index)
						queueConf.priorities.emplace_back(queueFamilyParam.priority);
				}
			}


			if (!bPresentableOk)
			{
				currentMissingQueueCount -= 1;
				break;
			}
		}

		// check if all queues are available
		if (currentMissingQueueCount == 0)
		{
			a_conf.emplace(deviceIndex, std::move(queueConf));
		}

		++deviceIndex;
	}
}