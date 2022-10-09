#include "pch.h"
#include "vk_Renderer.h"
#include "vk_struct_initializers.h"
#include "vk_logger.h"
#include <exception>


namespace Vulkan
{
	PFN_vkCreateDebugReportCallbackEXT VK_Renderer::vkCreateDebugReportCallbackEXT = nullptr;
	PFN_vkDestroyDebugReportCallbackEXT VK_Renderer::vkDestroyDebugReportCallbackEXT = nullptr;

	VkBool32 VKAPI_ATTR VK_Renderer::messageCallback(VkDebugReportFlagsEXT flags,				// Type of error
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
		{
			//Flag<VkDebugReportFlagBitsEXT>::to_string(flags);
			//to_string(objType);
		}
		return VK_FALSE;
	}

	VK_Renderer::VK_Renderer(const ApplicationInfo& a_appInfo, const RendererProps& a_props, VK_Logger* const a_pLogger) : m_debugCallbackHandle{ VK_NULL_HANDLE }
	{
		VkApplicationInfo appInfo = Vulkan::Initializers::applicationInfo();
		appInfo.apiVersion = VK_API_VERSION_1_3;
		appInfo.applicationVersion = a_appInfo.appVersion;
		appInfo.engineVersion = ENGINE_VERSION;
		appInfo.pApplicationName = a_appInfo.appName.c_str();
		appInfo.pEngineName = "VK";

		VkInstanceCreateInfo instCreateInfo = Vulkan::Initializers::instanceCreateInfo();
		instCreateInfo.pApplicationInfo = &appInfo;

		instCreateInfo.enabledExtensionCount = 0;
		instCreateInfo.ppEnabledExtensionNames = nullptr;

		instCreateInfo.enabledLayerCount = 0;
		instCreateInfo.ppEnabledLayerNames = nullptr;

		// check instance properties
		bool hasDebugExt = false;
		if (!checkInstanceExtensionProps(a_props.instanceProps, hasDebugExt))
			throw Vulkan::VK_Exception("unsupported extensions", std::source_location::current());

		// check layers
		if (!checkInstanceLayerProps(a_props.instanceLayers))
			throw Vulkan::VK_Exception("unsupported layers", std::source_location::current());

		instCreateInfo.enabledExtensionCount = static_cast<uint32_t>(a_props.instanceProps.size());
		instCreateInfo.ppEnabledExtensionNames = a_props.instanceProps.data();

		instCreateInfo.enabledLayerCount = static_cast<uint32_t>(a_props.instanceLayers.size());
		instCreateInfo.ppEnabledLayerNames = a_props.instanceLayers.data();

		VK_CHECK(vkCreateInstance(&instCreateInfo, nullptr, &m_vulkanInst));

		if (hasDebugExt)
		{
			VK_Renderer::vkCreateDebugReportCallbackEXT = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(m_vulkanInst, "vkCreateDebugReportCallbackEXT");
			VK_Renderer::vkDestroyDebugReportCallbackEXT = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(m_vulkanInst, "vkDestroyDebugReportCallbackEXT");
			if (vkCreateDebugReportCallbackEXT != nullptr && vkDestroyDebugReportCallbackEXT != nullptr)
			{
				// add debug callback
				VkDebugReportCallbackCreateInfoEXT debugExt = Vulkan::Initializers::debugCallbackCreateInfo();
				debugExt.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
				debugExt.pfnCallback = VK_Renderer::messageCallback;
				debugExt.pUserData = a_pLogger;
				VK_CHECK(vkCreateDebugReportCallbackEXT(m_vulkanInst, &debugExt, nullptr, &m_debugCallbackHandle));
			}
			else
			{
				throw Vulkan::VK_Exception("Failed to load PFN_vkCreateDebugUtilsMessengerEXT and vkDestroyDebugUtilsMessengerEXT functions", std::source_location::current());
			}
		}
	}

	VK_Renderer::~VK_Renderer()
	{
		if (m_debugCallbackHandle != VK_NULL_HANDLE)// optional
			vkDestroyDebugReportCallbackEXT(m_vulkanInst, m_debugCallbackHandle, nullptr);

		// release resources

		vkDestroyDevice(m_device.logicalDevice, nullptr);

		vkDestroyInstance(m_vulkanInst, nullptr);
	}

	void VK_Renderer::createDevice(const unsigned int a_deviceIndex)
	{
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(m_vulkanInst, &deviceCount, nullptr);
		
		std::vector<VkPhysicalDevice> deviceList(deviceCount);
		vkEnumeratePhysicalDevices(m_vulkanInst, &deviceCount, deviceList.data());

		m_device.physical = deviceList[a_deviceIndex];

		// get memory properties
		getDeviceCapabilities(m_device, m_deviceCapabilities);

		// get queues configuration
		RendererQueuesConfiguration queueConf;
		setupQueueConfiguration(m_deviceCapabilities.queueFamilies, queueConf);

		// create logical device
	}

	VkInstance VK_Renderer::vulkanInstance()const noexcept
	{
		return m_vulkanInst;
	}

	void VK_Renderer::setupQueueConfiguration(const std::vector<VkQueueFamilyProperties>& a_queuesProperties, RendererQueuesConfiguration& a_queueConf)const
	{
		int iFamilyIndex = 0;
		for (const auto& queueFamily : a_queuesProperties)
		{
			if (queueFamily.queueCount > 0)// at least on queue
			{
				// check if family supports graphics
				if ((queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) == VK_QUEUE_GRAPHICS_BIT)
				{
					//
				}
			}
			// todo
			++iFamilyIndex;
		}
	}
}