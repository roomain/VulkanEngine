#include "pch.h"
#include "vk_Renderer.h"
#include "vk_struct_initializers.h"
#include "vk_macros.h"
#include "vk_propFun.h"
#include <exception>


namespace Vulkan
{
	VK_Renderer* VK_Renderer::m_pInstance = nullptr;

	VkBool32  VK_Renderer::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData)
	{
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

	VK_Renderer::VK_Renderer(const ApplicationInfo& a_appInfo, const RendererProps a_props)
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
		if (checkInstanceLayerProps(a_props.instanceLayers))
			throw Vulkan::VK_Exception("unsupported layers", std::source_location::current());

		instCreateInfo.enabledExtensionCount = static_cast<uint32_t>(a_props.instanceProps.size());
		instCreateInfo.ppEnabledExtensionNames = a_props.instanceProps.data();

		instCreateInfo.enabledLayerCount = static_cast<uint32_t>(a_props.instanceLayers.size());
		instCreateInfo.ppEnabledLayerNames = a_props.instanceLayers.data();

		VK_CHECK(vkCreateInstance(&instCreateInfo, nullptr, &m_vulkanInst));
	}

	VK_Renderer::~VK_Renderer()
	{
		vkDestroyInstance(m_vulkanInst, nullptr);
	}
}