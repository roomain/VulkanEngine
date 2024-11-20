#include "pch.h"
#include <vector>
#include "VulkanContext.h"
#include "VulkanParameter.h"
#include "common/string_utils.h"
#include "common/contains.h"
#include "VulkanDevice.h"
#include "VulkanInitializers.h"


VulkanCapabilities VulkanContext::m_capabilities;

VulkanCapabilities& VulkanContext::getCapabilities()
{
	return m_capabilities;
}

VulkanContext::VulkanContext(const VulkanParameter& a_param, const char* const* a_extraExtension, const int a_numExt)
{
	std::vector<std::string> usedExtension = a_param.extensions;
	if (a_extraExtension != nullptr && a_numExt > 0)
	{
		for (int index = 0; index < a_numExt; ++index)
		{
			std::string ext{ a_extraExtension[index] };
			if(auto iter = std::ranges::find(a_param.extensions, ext); iter == a_param.extensions.cend())
				usedExtension.emplace_back(ext);
		}
	}

	// check instance ansd extensions
	if (!contains<VkExtensionProperties>(VulkanContext::m_capabilities.extensionBegin(), VulkanContext::m_capabilities.extensionEnd(), usedExtension,
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
	appInfo.apiVersion = VK_API_VERSION_1_0;// VK_VERSION_1_3;
	appInfo.applicationVersion = VulkanContext::m_appVersion;
	appInfo.engineVersion = VulkanContext::m_engineVersion;
	appInfo.pEngineName = "VulkanEngine";

	auto createInfo = Vulkan::Initializers::instanceCreateInfo();
	std::vector<const char*> extensions = vStringToChar(usedExtension);
	std::vector<const char*> layers = vStringToChar(a_param.layers);

	createInfo.enabledExtensionCount = static_cast<uint32_t>(usedExtension.size());
	createInfo.ppEnabledExtensionNames = extensions.data();
	createInfo.enabledLayerCount = static_cast<uint32_t>(a_param.layers.size());
	createInfo.ppEnabledLayerNames = layers.data();
	createInfo.pApplicationInfo = &appInfo;

	VK_CHECK_EXCEPT(vkCreateInstance(&createInfo, nullptr, &m_instance));
}

bool VulkanContext::isValid()const noexcept
{
	return m_instance != VK_NULL_HANDLE;
}

VulkanDevicePtr VulkanContext::createNewDevice(const VulkanDeviceParameter& a_param, DeviceChoice a_choose, VkSurfaceKHR a_surface)
{
	VulkanDevicePtr vulkanDev;
	std::vector<int> vCompatibleDevice;
	int deviceIndex = 0;

	// available devices configurations
	struct DeviceQueuesConf
	{
		std::vector<VkDeviceQueueCreateInfo> baseCreateInfo;
		std::vector<float> priorities;// size = Sum of queues in baseCreateInfo
	};

	std::unordered_map<int, DeviceQueuesConf> devicesConf;
	std::vector<int> compatibleDevices;

	// find compatible devices
	for (auto deviceCap = VulkanContext::m_capabilities.deviceBegin(); deviceCap != VulkanContext::m_capabilities.deviceEnd(); ++deviceCap)
	{
		// check layers
		if (!contains<VkLayerProperties>(deviceCap->layerBegin(), deviceCap->layerEnd(), a_param.layers,
			[](const std::string_view& a_search, const VkLayerProperties& a_layer)
			{
				return a_search.compare(a_layer.layerName) == 0;
			}))
			continue;

		// check extensions
		if (!contains<VkExtensionProperties>(deviceCap->extensionBegin(), deviceCap->extensionEnd(), a_param.extensions,
			[](const std::string_view& a_search, const VkExtensionProperties& a_extension)
			{
				return a_search.compare(a_extension.extensionName) == 0;
			}))
			continue;

		if (!deviceCap->isFeaturesAvailable(a_param.features))
			continue;

		DeviceQueuesConf queueConf;

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
							.flags = queueFamilyParam.flags,
							.queueFamilyIndex = queueFamilyIndex,
							.queueCount = minKeep,
							.pQueuePriorities = nullptr
						}
					);
					for (uint32_t index = 0; index < minKeep; ++index)
						queueConf.priorities.emplace_back(queueFamilyParam.priority);
				}
				queueFamilyIndex++;
			}
			missingQueueCount += queueFamilyParam.count;
		}

		// check if all queues are available
		if (missingQueueCount == 0)
		{
			devicesConf.emplace(deviceIndex, std::move(queueConf));
			compatibleDevices.emplace_back(deviceIndex);
		}

		++deviceIndex;
	}

	if (!compatibleDevices.empty())
	{
		int chosenDevice = compatibleDevices[0];
		// by default get first device else (need a other parameter for user device choice maybe a function)
		if (compatibleDevices.size() > 1)
		{
			chosenDevice = a_choose(compatibleDevices);
		}


		auto vExtents = vStringToChar(a_param.extensions);
		auto vLayers = vStringToChar(a_param.layers);
		auto features = VulkanDeviceCapabilities::toFeatures(a_param.features);
		VkDeviceCreateInfo devInfo = Vulkan::Initializers::deviceCreateInfo();


		devInfo.flags = static_cast<VkDeviceCreateFlags>(0);
		devInfo.queueCreateInfoCount = static_cast<uint32_t>(devicesConf[chosenDevice].baseCreateInfo.size());

		// set queue priority to conf struct
		float* iter = devicesConf[chosenDevice].priorities.data();
		for (auto& queueConf : devicesConf[chosenDevice].baseCreateInfo)
		{
			queueConf.pQueuePriorities = iter;
			iter += queueConf.queueCount;
		}

		devInfo.pQueueCreateInfos = devicesConf[chosenDevice].baseCreateInfo.data();
		devInfo.enabledExtensionCount = static_cast<uint32_t>(a_param.extensions.size());
		devInfo.ppEnabledExtensionNames = vExtents.data();
		devInfo.enabledLayerCount = static_cast<uint32_t>(a_param.layers.size());
		devInfo.ppEnabledLayerNames = vLayers.data();
		devInfo.pEnabledFeatures =  &features;

		VkDevice logical;
		VK_CHECK_EXCEPT(vkCreateDevice((VulkanContext::m_capabilities.deviceBegin() + chosenDevice)->physicalDevice(),
			&devInfo, nullptr, &logical))

		vulkanDev = std::shared_ptr<VulkanDevice>(new VulkanDevice((VulkanContext::m_capabilities.deviceBegin() + chosenDevice)->physicalDevice(),
			logical));
	}
	return vulkanDev;
}