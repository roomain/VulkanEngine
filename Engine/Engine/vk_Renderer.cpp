#include "pch.h"
#include "vk_Renderer.h"
#include "vk_struct_initializers.h"
#include "vk_macros.h"
#include "vk_propFun.h"
#include "vk_logger.h"
#include <exception>


namespace Vulkan
{

	VK_Renderer* VK_Renderer::m_pInstance = nullptr;
	PFN_vkCreateDebugUtilsMessengerEXT VK_Renderer::vkCreateDebugUtilsMessengerEXT = nullptr;
	PFN_vkDestroyDebugUtilsMessengerEXT VK_Renderer::vkDestroyDebugUtilsMessengerEXT = nullptr;

	VkBool32  VK_Renderer::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData)
	{
		VK_Logger* const pLogger = static_cast<VK_Logger*>(pUserData);
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
		return 0;
	}

	VK_Renderer::VK_Renderer(const ApplicationInfo& a_appInfo, const RendererProps a_props, VK_Logger* const a_pLogger) : m_debugMessangerHandle{ VK_NULL_HANDLE }
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
		if (checkInstanceExtensionProps(a_props.instanceProps))
			throw Vulkan::VK_Exception("unsupported extensions", std::source_location::current());

		// check layers
		bool hasDebugLayer = false;
		if (checkInstanceLayerProps(a_props.instanceLayers, hasDebugLayer))
			throw Vulkan::VK_Exception("unsupported layers", std::source_location::current());

		instCreateInfo.enabledExtensionCount = static_cast<uint32_t>(a_props.instanceProps.size());
		instCreateInfo.ppEnabledExtensionNames = a_props.instanceProps.data();

		instCreateInfo.enabledLayerCount = static_cast<uint32_t>(a_props.instanceLayers.size());
		instCreateInfo.ppEnabledLayerNames = a_props.instanceLayers.data();

		VK_CHECK(vkCreateInstance(&instCreateInfo, nullptr, &m_vulkanInst));

		if (hasDebugLayer)
		{
			// add debug callback
			VkDebugUtilsMessengerCreateInfoEXT debugExt = Vulkan::Initializers::messageCallbackCreateInfo();
			debugExt.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
			debugExt.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
			debugExt.pfnUserCallback = VK_Renderer::debugCallback;
			debugExt.pUserData = a_pLogger;

			VK_Renderer::vkCreateDebugUtilsMessengerEXT = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_vulkanInst, "vkCreateDebugUtilsMessengerEXT");
			VK_Renderer::vkDestroyDebugUtilsMessengerEXT = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_vulkanInst, "vkDestroyDebugUtilsMessengerEXT");
			if (vkCreateDebugUtilsMessengerEXT != nullptr && vkDestroyDebugUtilsMessengerEXT != nullptr)
			{
				VK_CHECK(vkCreateDebugUtilsMessengerEXT(m_vulkanInst, &debugExt, nullptr, &m_debugMessangerHandle));
			}
			else
			{
				throw Vulkan::VK_Exception("Failed to load PFN_vkCreateDebugUtilsMessengerEXT and vkDestroyDebugUtilsMessengerEXT functions", std::source_location::current());
			}
		}
	}

	VK_Renderer::~VK_Renderer()
	{
		if (m_debugMessangerHandle != VK_NULL_HANDLE)// optional
			vkDestroyDebugUtilsMessengerEXT(m_vulkanInst, m_debugMessangerHandle, nullptr);

		// release resources

		vkDestroyDevice(m_device.logicalDevice, nullptr);

		vkDestroyInstance(m_vulkanInst, nullptr);
	}
}