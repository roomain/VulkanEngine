#include "pch.h"
#include "VulkanContext.h"
#include "VulkanParameter.h"
#include "common/string_utils.h"
#include "common/contains.h"


VulkanCapabilities VulkanContext::m_capabilities;

VulkanCapabilities& VulkanContext::getCapabilities()
{
	return m_capabilities;
}

VulkanContext::VulkanContext(const VulkanParameter& a_param)
{
	// check instance ansd extensions
	if (!contains<VkExtensionProperties>(VulkanContext::m_capabilities.extensionBegin(), VulkanContext::m_capabilities.extensionEnd(), a_param.extensions,
		[](const std::string_view& a_search, const VkExtensionProperties& a_extension)
		{
			return a_search.compare(a_extension.extensionName) == 0;
		}))
	{
		throw Exception("Some extension are not supported");
	}
	
	if (!contains<VkLayerProperties>(VulkanContext::m_capabilities.layerBegin(), VulkanContext::m_capabilities.layerEnd(), a_param.layers,
		[](const std::string_view& a_search, const VkLayerProperties& a_layer)
		{
			return a_search.compare(a_layer.layerName) == 0;
		}))
	{
		throw Exception("Some extension are not supported");
	}

	// create instance
	auto appInfo = Vulkan::Initializers::applicationInfo();
	appInfo.apiVersion = VK_VERSION_1_3;
	appInfo.applicationVersion = VulkanContext::m_appVersion;
	appInfo.engineVersion = VulkanContext::m_engineVersion;
	appInfo.pEngineName = "VulkanEngine";

	auto createInfo = Vulkan::Initializers::instanceCreateInfo();
	std::vector<const char*> extensions = vStringToChar(a_param.extensions);
	std::vector<const char*> layers = vStringToChar(a_param.layers);

	createInfo.enabledExtensionCount = static_cast<uint32_t>(a_param.extensions.size());
	createInfo.ppEnabledExtensionNames = extensions.data();
	createInfo.enabledLayerCount = static_cast<uint32_t>(a_param.layers.size());
	createInfo.ppEnabledLayerNames = layers.data();
	createInfo.pApplicationInfo = &appInfo;
	
	vkCreateInstance(&createInfo, nullptr, &m_instance);
}

bool VulkanContext::isValid()const noexcept
{
	return m_instance != VK_NULL_HANDLE;
}

VulkanDevicePtr VulkanContext::createNewDevice(const VulkanDeviceParameter& a_param, VkSurfaceKHR a_surface)
{
	VulkanDevicePtr vulkanDev;
	std::vector<int> vCompatibleDevice;
	int deviceIndex = 0;

	// find compatible devices
	for (auto deviceCap = VulkanContext::m_capabilities.deviceBegin(); deviceCap != VulkanContext::m_capabilities.deviceEnd(); ++deviceCap)
	{
		// check layers
		if (!contains<VkLayerProperties>(deviceCap->layerBegin(), deviceCap->layerEnd(), a_param.layers,
			[](const std::string_view& a_search, const VkLayerProperties& a_layer)
			{
				return a_search.compare(a_layer.layerName) == 0;
			}))
		{
			continue;
		}

		// check extensions
		if (!contains<VkExtensionProperties>(deviceCap->extensionBegin(), deviceCap->extensionEnd(), a_param.extensions,
			[](const std::string_view& a_search, const VkExtensionProperties& a_extension)
			{
				return a_search.compare(a_extension.extensionName) == 0;
			}))
		{
			continue;
		}

		// contains number of available queue per family
		std::unordered_map<int, uint32_t> QueuesFamilyRemainQueues; 
		int missingQueueCount = 0;
		for (auto queueFamilyParam : a_param.queues)// need a copy
		{
			uint32_t queueFamilyIndex = 0;
			for (auto iter = deviceCap->queueBegin(); iter != deviceCap->queueEnd() && (queueFamilyParam.count > 0); ++iter)
			{
				if ((iter->queueFlags & queueFamilyParam.flags) == queueFamilyParam.flags)
				{
					if (a_surface && queueFamilyParam.bIsRenderer)
					{
						VkBool32 supported = false;
						VK_CHECK_LOG(vkGetPhysicalDeviceSurfaceSupportKHR(deviceCap->physicalDevice(), queueFamilyIndex, a_surface, &supported))
						if (!supported)
							continue;
					}

					
					if (auto iterQueue = QueuesFamilyRemainQueues.find(queueFamilyIndex); iterQueue != QueuesFamilyRemainQueues.end())
					{
						int minKeep = std::min(iterQueue->second, queueFamilyParam.count);
						iterQueue->second -= minKeep;
						queueFamilyParam.count -= minKeep;
					}
					else
					{
						int minKeep = std::min(iter->queueCount, queueFamilyParam.count);
						QueuesFamilyRemainQueues[queueFamilyIndex] = iter->queueCount - minKeep;
						queueFamilyParam.count -= minKeep;
					}
				}
				queueFamilyIndex++;
			}
			missingQueueCount += queueFamilyParam.count;
		}

		// check if all queues are available
		if (missingQueueCount == 0)
		{
			// todo
		}

		++deviceIndex;
	}

	// by default get first device else (need a other parameter for user device choice maybe a function)

	//
	//vkCreateDevice()
	//
	return vulkanDev;
}