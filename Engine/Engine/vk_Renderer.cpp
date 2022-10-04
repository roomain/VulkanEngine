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
		/*switch (messageSeverity)
		{
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
			return 0;
			//std::cerr << " VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT";
			//break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
			std::cerr << " VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT";
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
			std::cerr << " VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT";
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
			std::cerr << " VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT";
			break;
		}


		switch (messageType)
		{
		case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT:
			std::cerr << " VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT";
			break;
		case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT:
			std::cerr << " VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT";
			break;
		case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT:
			std::cerr << " VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT";
			break;
		}
		std::cerr << std::endl << pCallbackData->pMessageIdName << std::endl << pCallbackData->pMessage << std::endl;
		std::cerr << "-------------------------------------------" << std::endl;*/
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

	VkInstance VK_Renderer::vulkanInstance()const noexcept
	{
		return m_vulkanInst;
	}
}