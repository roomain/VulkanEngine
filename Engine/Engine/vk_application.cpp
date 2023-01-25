#include "pch.h"
#include <algorithm>
#include <iterator>
#include "vk_display.h"
#include "IDisplayer.h"
#include "vk_configuration.h"
#include "vk_logger.h"
#include "vk_WindowSystemProxy.h"
#include "vk_Renderer.h"


namespace Vulkan
{
	VK_Application* VK_Application::m_pInstance = nullptr;
	PFN_vkCreateDebugReportCallbackEXT VK_Application::vkCreateDebugReportCallbackEXT = nullptr;
	PFN_vkDestroyDebugReportCallbackEXT VK_Application::vkDestroyDebugReportCallbackEXT = nullptr;
	
	VK_Application::VK_Application() : m_vulkanInst{ VK_NULL_HANDLE }, m_debugCallbackHandle{VK_NULL_HANDLE}
	{
		// get  vulkan instance capabilities
		uint32_t propCount = 0;
		vkEnumerateInstanceLayerProperties(&propCount, nullptr);
		m_capabilities.layerPops.resize(propCount);
		vkEnumerateInstanceLayerProperties(&propCount, m_capabilities.layerPops.data());

		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
		m_capabilities.extensionProps.resize(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, m_capabilities.extensionProps.data());
	}

	VK_Application* const VK_Application::instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new VK_Application();
		return m_pInstance;
	}

	VK_Application::~VK_Application()
	{
		// TODO

		if (m_debugCallbackHandle != VK_NULL_HANDLE)// optional
			vkDestroyDebugReportCallbackEXT(m_vulkanInst, m_debugCallbackHandle, nullptr);
		m_debugCallbackHandle = VK_NULL_HANDLE;

		if (VK_NULL_HANDLE != m_vulkanInst)
			vkDestroyInstance(m_vulkanInst, nullptr);
	}

	void VK_Application::createVulkanInstance(const InstanceConf& a_conf, VK_Logger* const a_pLogger)
	{
		// create vulkan instance
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
		std::vector<const char*> vNameData;
		std::transform(a_conf.instanceExtProps.begin(), a_conf.instanceExtProps.end(), std::back_inserter(vNameData), 
			[](const auto& ext) {return ext.c_str(); });

		std::transform(a_conf.instanceLayers.begin(), a_conf.instanceLayers.end(), std::back_inserter(vNameData),
			[](const auto& layer) {return layer.c_str(); });

		instCreateInfo.enabledExtensionCount = static_cast<uint32_t>(a_conf.instanceExtProps.size());
		instCreateInfo.ppEnabledExtensionNames = vNameData.data();

		instCreateInfo.enabledLayerCount = static_cast<uint32_t>(a_conf.instanceLayers.size());
		instCreateInfo.ppEnabledLayerNames = &vNameData[a_conf.instanceExtProps.size()];

		VK_CHECK(vkCreateInstance(&instCreateInfo, nullptr, &m_vulkanInst));

		// create Debug
		if (a_conf.useDebug)
		{
			VK_Application::vkCreateDebugReportCallbackEXT = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(m_vulkanInst, "vkCreateDebugReportCallbackEXT");
			VK_Application::vkDestroyDebugReportCallbackEXT = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(m_vulkanInst, "vkDestroyDebugReportCallbackEXT");
			if (vkCreateDebugReportCallbackEXT != nullptr && vkDestroyDebugReportCallbackEXT != nullptr)
			{
				// add debug callback
				VkDebugReportCallbackCreateInfoEXT debugExt = Vulkan::Initializers::debugCallbackCreateInfo();
				debugExt.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
				debugExt.pfnCallback = VK_Application::messageCallback;
				debugExt.pUserData = a_pLogger;
				VK_CHECK(vkCreateDebugReportCallbackEXT(m_vulkanInst, &debugExt, nullptr, &m_debugCallbackHandle));
			}
			else
			{
				throw VK_Exception("Failed to load PFN_vkCreateDebugUtilsMessengerEXT and vkDestroyDebugUtilsMessengerEXT functions", std::source_location::current());
			}
		}
		//--------------------------------------------------------------------------------
		//Get devices capabilities
		uint32_t uiDeviceCount = 0;
		VK_CHECK(vkEnumeratePhysicalDevices(m_vulkanInst, &uiDeviceCount, nullptr));
		if (uiDeviceCount > 0)
		{
			std::vector<VkPhysicalDevice> physicalDevices(static_cast<size_t>(uiDeviceCount));
			VK_CHECK(vkEnumeratePhysicalDevices(m_vulkanInst, &uiDeviceCount, physicalDevices.data()));

			m_vDeviceCapabilities.resize(uiDeviceCount);
			int index = 0;
			for (const auto& physicalDev : physicalDevices)
			{
				m_vDeviceCapabilities[index].physicalDevice = physicalDev;
				getDeviceCapabilities(physicalDev, m_vDeviceCapabilities[index]);
				++index;
			}
		}
	}

	bool VK_Application::checkInstanceLayer(const std::string& a_layer)const noexcept
	{
		return std::any_of(m_capabilities.layerPops.begin(), m_capabilities.layerPops.end(),
			[&a_layer](const auto& lay) {return a_layer.compare(lay.layerName) == 0; });
	}

	bool VK_Application::checkInstanceLayers(const std::vector<std::string>& a_vLayer)const noexcept
	{
		return !std::any_of(a_vLayer.begin(), a_vLayer.end(), [this](const auto& layer) {return !checkInstanceLayer(layer); });
	}

	bool VK_Application::checkInstanceExtension(const std::string& a_ext)const noexcept
	{
		return std::any_of(m_capabilities.extensionProps.begin(), m_capabilities.extensionProps.end(), 
			[&a_ext](const auto& ext) {return a_ext.compare(ext.extensionName) == 0; });
	}

	bool VK_Application::checkInstanceExtensions(const std::vector<std::string>& a_vExt)const noexcept
	{
		return !std::any_of(a_vExt.begin(), a_vExt.end(), [this](const auto& ext) {return !checkInstanceExtension(ext); });
	}

	void VK_Application::displayInstanceCapabilities(IDisplayer& a_displayer)const
	{
		a_displayer.beginNode("Instance capabilities");
		a_displayer.beginNode("Instance Layer Properties");
		for (const auto& prop : m_capabilities.layerPops)
		{
			a_displayer.beginNode(prop.layerName);
			a_displayer.attribute("Description", prop.description);
			a_displayer.attribute("Implementation version", prop.implementationVersion);
			a_displayer.attribute("Specific version", prop.specVersion);
			a_displayer.endNode();
		}
		a_displayer.endNode();
		//--------------------------------------------------------------------------
		a_displayer.beginNode("Instance Extensions");
		for (const auto& extend : m_capabilities.extensionProps)
		{
			a_displayer.beginNode(extend.extensionName);
			a_displayer.attribute("Specific version", extend.specVersion);
			a_displayer.endNode();
		}
		a_displayer.endNode();
		a_displayer.endNode();
	}

	void VK_Application::displayDevicesCapabilities(IDisplayer& a_displayer)const
	{
		if (VK_NULL_HANDLE == m_vulkanInst)
			throw VK_Exception("Vulkan instance is missing!", std::source_location::current());
		
		a_displayer.beginNode("Physical Devices");
		for (const auto& physicalDevCapabilities : m_vDeviceCapabilities)
		{
			a_displayer.beginNode("Physical Device");
			displayDeviceproperties(physicalDevCapabilities.deviceProperties, a_displayer);

			//---------------------------------------------------------------------------------------------
			displayDeviceFeatures(physicalDevCapabilities.deviceFeatures, a_displayer);

			displayDeviceMemoryProperties(physicalDevCapabilities.memoryProperties, a_displayer);

			a_displayer.beginNode("Device Extensions");
			for (const auto& ext : physicalDevCapabilities.extensions)
				a_displayer.attribute(std::string(ext.extensionName), ext.specVersion);
			a_displayer.endNode();

			displayDeviceFormats(physicalDevCapabilities.formatsProperties, a_displayer);

			displayDeviceFormats(physicalDevCapabilities.swapChanCapabilities, a_displayer);

			displayDeviceQueuesproperties(physicalDevCapabilities.queueFamilies, a_displayer);

			a_displayer.endNode();
		}
		a_displayer.endNode();
	}

	void VK_Application::searchCompatibleDevice(const VulkanConfiguration& a_conf, std::vector<DeviceInfo>& a_vDevice, const std::shared_ptr<VK_WindowSystemProxy>& a_winProxy)
	{
		int iDeviceIndex = 0;
		// check if queue support surface for graphical: vkGetPhysicalDeviceSurfaceSupportKHR (QueueConfiguration::presentationSupport)
		for (const auto& devCap : m_vDeviceCapabilities)
		{		
			DeviceQueuesConfiguration tempQueueConf = a_conf.queues;
			for (auto& queueConf : tempQueueConf.vQueueConf)
			{
				int iFamilyIndex = 0;
				for (const auto& queueCap : devCap.queueFamilies)
				{
					if (queueCap.queueCount > 0)
					{
						if (queueConf.type == (queueConf.type & queueCap.queueFlags))
						{
							queueConf.index = iFamilyIndex;
							if (a_winProxy)
							{
								VkBool32 presentationSupport = VK_FALSE;
								VK_CHECK(vkGetPhysicalDeviceSurfaceSupportKHR(devCap.physicalDevice, iFamilyIndex, a_winProxy->surface(), &presentationSupport))
								queueConf.presentationSupport = presentationSupport == VK_TRUE;
							}
						}
					}
					++iFamilyIndex;
				}
			}

			if (tempQueueConf.isValid())
				a_vDevice.emplace_back(iDeviceIndex, devCap.deviceProperties.deviceName, to_string(devCap.deviceProperties.deviceType), devCap.deviceProperties.apiVersion, devCap.deviceProperties.driverVersion);
			
			++iDeviceIndex;
		}
	}
	
	std::shared_ptr<VK_Renderer> VK_Application::createRenderer(const VulkanConfiguration& a_conf, const DeviceInfo& a_chosenDevice, const std::shared_ptr<VK_WindowSystemProxy>& a_winProxy)
	{
		if(m_vulkanInst == VK_NULL_HANDLE)
			throw VK_Exception("Can't create renderer without Vulkan instance.", std::source_location::current());
		
		RenderDeviceConf renderConf;
		renderConf.vkInstance = m_vulkanInst;
		renderConf.frameTimeout = a_conf.frameTimeout;
		renderConf.useDepthBuffer = a_conf.useDepthBuffer;
		renderConf.queueConf = a_conf.queues;
		for (auto& queueConf : renderConf.queueConf.vQueueConf)
		{
			int iFamilyIndex = 0;
			for (const auto& queueCap : m_vDeviceCapabilities[a_chosenDevice.deviceIndex].queueFamilies)
			{
				if (queueCap.queueCount > 0)
				{
					if (queueConf.type == (queueConf.type & queueCap.queueFlags))
					{
						queueConf.index = iFamilyIndex;
						if (a_winProxy)
						{
							VkBool32 presentationSupport = VK_FALSE;
							VK_CHECK(vkGetPhysicalDeviceSurfaceSupportKHR(m_vDeviceCapabilities[a_chosenDevice.deviceIndex].physicalDevice, iFamilyIndex, a_winProxy->surface(), &presentationSupport))
							queueConf.presentationSupport = presentationSupport == VK_TRUE;
						}
					}
				}
				++iFamilyIndex;
			}
		}

		return std::make_shared<VK_Renderer>(m_vDeviceCapabilities[a_chosenDevice.deviceIndex].physicalDevice, std::move(renderConf),
			a_conf.deviceExt, a_winProxy);
	}
	//-----------------------------------------------------------------------------------------------------------------------
	VkBool32 VKAPI_ATTR VK_Application::messageCallback(VkDebugReportFlagsEXT flags,				// Type of error
		VkDebugReportObjectTypeEXT objType,			// Type of object causing error
		uint64_t obj,								// ID of object
		size_t location,
		int32_t code,
		const char* layerPrefix,
		const char* message,						// Validation Information
		void* userData)
	{
		VK_Logger* const pLogger = static_cast<VK_Logger*>(userData);
		if (pLogger)
			pLogger->log(flags, objType, obj, location, code, layerPrefix, message);
		return VK_FALSE;
	}
}