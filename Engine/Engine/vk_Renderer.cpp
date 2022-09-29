#include "pch.h"
#include "vk_Renderer.h"
#include "vk_struct_initializers.h"
#include "vk_macros.h"
#include "vk_propFun.h"


namespace Vulkan
{
	VK_Renderer* VK_Renderer::m_pInstance = nullptr;

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
			throw;

		// check layers
		if (checkInstanceLayerProps(a_props.instanceLayers))
			throw;

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