#include "pch.h"
#include <algorithm>
#include <iterator>
#include "IDataDisplayer.h"
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
		//
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
		std::transform(a_conf.instanceExtProps.cbegin(), a_conf.instanceExtProps.cend(), std::back_inserter(vNameData), 
			[](const auto& ext) {return ext.c_str(); });

		std::transform(a_conf.instanceLayers.cbegin(), a_conf.instanceLayers.cend(), std::back_inserter(vNameData),
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
		VK_VulkanCapabilities::instance().enumerateDeviceCapabilities(m_vulkanInst);
	}

	
	std::shared_ptr<VK_Renderer> VK_Application::createRenderer(const VulkanConfiguration& a_conf, const DeviceInfo& a_chosenDevice, const std::shared_ptr<VK_WindowSystemProxy>& a_winProxy)const
	{
		if(m_vulkanInst == VK_NULL_HANDLE)
			throw VK_Exception("Can't create renderer without Vulkan instance.", std::source_location::current());
		
		RenderDeviceConf renderConf;
		renderConf.vkInstance = m_vulkanInst;
		renderConf.frameTimeout = a_conf.frameTimeout;
		renderConf.useDepthBuffer = a_conf.useDepthBuffer;
		renderConf.queueConf = a_conf.queues;

		VK_VulkanCapabilities::instance()[a_chosenDevice.deviceIndex].queues(a_winProxy, renderConf.queueConf);

		return std::make_shared<VK_Renderer>(a_chosenDevice.deviceIndex, std::move(renderConf), a_conf.deviceExt, a_winProxy);
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