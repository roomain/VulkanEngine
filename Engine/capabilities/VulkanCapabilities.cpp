#include "pch.h"
#include "VulkanCapabilities.h"
#include "common/enumerate.h"
#include "VulkanInitializers.h"
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
	enumerate(&vkEnumeratePhysicalDevices, m_physicalDevices, m_instance);
	int index = 0;
	for (const auto& physicalDev : m_physicalDevices)
	{
		m_devicesCap.emplace_back(VulkanDeviceCapabilities(index ,physicalDev));
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
	return m_devicesCap.cbegin();
}

VulkanCapabilities::Device_const_iterator VulkanCapabilities::deviceEnd()const noexcept
{
	return m_devicesCap.cend();
}

void VulkanCapabilities::findDeviceCompatibleConfiguration(const VulkanDeviceParameter& a_parameters, VulkanDeviceConfMap& a_conf, VkSurfaceKHR a_surface)const
{	
	int deviceIndex = 0;
	for (const auto& deviceCap : m_devicesCap)
	{
		// check layers
		if (!contains<VkLayerProperties>(deviceCap.m_layersProperties.cbegin(), deviceCap.m_layersProperties.cend(), a_parameters.layers,
			[](const std::string_view& a_search, const VkLayerProperties& a_layer)
			{
				return a_search.compare(a_layer.layerName) == 0;
			}))
			continue;

		// check extensions
		if (!contains<VkExtensionProperties>(deviceCap.m_extensions.cbegin(), deviceCap.m_extensions.cend(), a_parameters.extensions,
			[](const std::string_view& a_search, const VkExtensionProperties& a_extension)
			{
				return a_search.compare(a_extension.extensionName) == 0;
			}))
			continue;

		if (!deviceCap.isFeaturesAvailable(a_parameters.features))
			continue;

		VulkanDeviceConf devConf{
			.physicalDev = m_physicalDevices[deviceCap.m_deviceIndex]
		};

		// contains number of available queue per family
		std::unordered_map<uint32_t, uint32_t> QueuesFamilyRemainQueues;
		int currentMissingQueueCount = 0;

		
		for (auto queueFamilyParam : a_parameters.queues)// need a copy
		{
			uint32_t queueFamilyIndex = 0;
			bool bPresentableOk = !queueFamilyParam.bPresentationAvailable;

			// search compatible queue
			for (auto iter = deviceCap.m_queueFamilies.cbegin(); iter != deviceCap.m_queueFamilies.cend() && (queueFamilyParam.count > 0); ++iter)
			{
				bool isGraphics = false;
				if ((iter->queueFlags & static_cast<VkQueueFlags>(queueFamilyParam.flags)) == static_cast<VkQueueFlags>(queueFamilyParam.flags))
				{
					static constexpr VkQueueFlags graphicFlag = static_cast<VkQueueFlags>(VK_QUEUE_GRAPHICS_BIT);
					isGraphics = (static_cast<VkQueueFlags>(queueFamilyParam.flags) & graphicFlag) == graphicFlag;
					if (a_surface && queueFamilyParam.bPresentationAvailable)
					{
						VkBool32 supported = false;
						VK_CHECK_LOG(vkGetPhysicalDeviceSurfaceSupportKHR(devConf.physicalDev, queueFamilyIndex, a_surface, &supported))
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

					if (isGraphics)
						devConf.graphicQueueIndex = static_cast<int>(devConf.baseCreateInfo.size());

					if (bPresentableOk)
						devConf.presentationQueueIndex = static_cast<int>(devConf.baseCreateInfo.size());

					devConf.queueFlags.emplace_back(iter->queueFlags);
					devConf.baseCreateInfo.emplace_back(
						VkDeviceQueueCreateInfo{
							.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
							.pNext = nullptr,
							.flags = 0,
							.queueFamilyIndex = queueFamilyIndex,
							.queueCount = minKeep,
							.pQueuePriorities = nullptr
						}
					);
					
					for (uint32_t index = 0; index < minKeep; ++index)
						devConf.priorities.emplace_back(queueFamilyParam.priority);
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
			int Offset = 0;
			for (auto& queueInfo : devConf.baseCreateInfo)
			{
				queueInfo.pQueuePriorities = devConf.priorities.data() + Offset;
				Offset += queueInfo.queueCount;
			}

			a_conf.emplace(deviceIndex, std::move(devConf));
		}

		++deviceIndex;
	}
}