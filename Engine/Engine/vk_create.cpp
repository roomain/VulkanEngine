#include "pch.h"

namespace Vulkan
{
	constexpr uint32_t ENGINE_VERSION = 1;								/*!< engine version*/

	void createVulkanInstance(const VulkanConfiguration& a_conf, VkInstance& a_vkInstance)
	{
		VkApplicationInfo appInfo = Vulkan::Initializers::applicationInfo();
		appInfo.apiVersion = VK_API_VERSION_1_3;
		appInfo.applicationVersion = a_conf.appVersion;
		appInfo.engineVersion = ENGINE_VERSION;
		appInfo.pApplicationName = a_conf.appName.c_str();
		appInfo.pEngineName = "VK_Engine";

		VkInstanceCreateInfo instCreateInfo = Vulkan::Initializers::instanceCreateInfo();
		instCreateInfo.pApplicationInfo = &appInfo;

		instCreateInfo.enabledExtensionCount = 0;
		instCreateInfo.ppEnabledExtensionNames = nullptr;

		instCreateInfo.enabledLayerCount = 0;
		instCreateInfo.ppEnabledLayerNames = nullptr;

		// generate table of char* from vectors of string
		size_t size = a_conf.instanceExtProps.size() + a_conf.instanceLayers.size();
		std::vector<const char*> vNameData;
		//const char** tabProp = new const char* [size];
		int iIndex = 0;
		for (auto& ext : a_conf.instanceExtProps)
			vNameData.emplace_back(ext.c_str());

		for (auto& layer : a_conf.instanceLayers)
			vNameData.emplace_back(layer.c_str());

		instCreateInfo.enabledExtensionCount = static_cast<uint32_t>(a_conf.instanceExtProps.size());
		instCreateInfo.ppEnabledExtensionNames = vNameData.data();

		instCreateInfo.enabledLayerCount = static_cast<uint32_t>(a_conf.instanceLayers.size());
		instCreateInfo.ppEnabledLayerNames = &vNameData[a_conf.instanceExtProps.size()];

		VK_CHECK(vkCreateInstance(&instCreateInfo, nullptr, &a_vkInstance));
	}

	void createVulkanDevice(const RendererQueuesConfiguration& a_queueConf, const std::vector<std::string>& a_deviceExt, Device& a_device)
	{
		// create queues create info for the device
		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::vector<float> vPriorities(a_queueConf.vQueueConf.size());
		std::fill(vPriorities.begin(), vPriorities.end(), 1.0f);

		int index = 0;
		for (const auto& conf : a_queueConf.vQueueConf)
		{
			auto createInfo = Initializers::queueCreateInfo();
			createInfo.queueCount = 1;
			createInfo.queueFamilyIndex = conf.index;
			createInfo.pQueuePriorities = &vPriorities[index];
			queueCreateInfos.emplace_back(std::move(createInfo));
			++index;
		}

		// info for create logical device
		VkDeviceCreateInfo deviceCreateInfo = Initializers::deviceCreateInfo();
		deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());		// Number of Queue Create Infos
		deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();								// List of queue create infos so device can create required queues
		deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(a_deviceExt.size());			// Number of enabled logical device extensions
		std::vector<const char*> vExtNames;
		for(const auto& name : a_deviceExt)
			vExtNames.emplace_back(name.c_str());
		
		deviceCreateInfo.ppEnabledExtensionNames = vExtNames.data();
		VK_CHECK(vkCreateDevice(a_device.physical, &deviceCreateInfo, nullptr, &a_device.logicalDevice))
	}
}