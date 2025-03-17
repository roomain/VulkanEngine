#include "pch.h"
#include <vector>
#include <format>
#include <memory>
#include "VulkanContext.h"
#include "VulkanParameter.h"
#include "VulkanDevice.h"
#include "VulkanDeviceCapabilities.h"

#if defined(WIN32)
#include "vulkan/vulkan_win32.h"
#endif



VkBool32 VulkanContext::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT a_messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT /*a_messageTypes*/,
	const VkDebugUtilsMessengerCallbackDataEXT* a_pCallbackData,
	void* a_pUserData)
{
	const VulkanContext* vulkanCtxt = static_cast<VulkanContext*>(a_pUserData);
	if (vulkanCtxt->m_debugCallback)
	{
		const std::string message = std::format("[{}] - {}", to_string(a_messageSeverity), a_pCallbackData->pMessage);
		vulkanCtxt->m_debugCallback(message.c_str());
		return true;
	}
	return false;
}

VulkanContext::VulkanContext(const VulkanParameter& a_param, DebugLog a_debugCallback, const char* const* a_extraExtension, const int a_numExt) : m_debugCallback{a_debugCallback}
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
	if (!contains<VkExtensionProperties>(VulkanCapabilities::extensionBegin(), VulkanCapabilities::extensionEnd(), usedExtension,
		[](const std::string_view& a_search, const VkExtensionProperties& a_extension)
		{
			return a_search.compare(a_extension.extensionName) == 0;
		}))
	{
		throw Exception("Some extension are not supported");
	}

	if (!contains<VkLayerProperties>(VulkanCapabilities::layerBegin(), VulkanCapabilities::layerEnd(), a_param.layers,
		[](const std::string_view& a_search, const VkLayerProperties& a_layer)
		{
			return a_search.compare(a_layer.layerName) == 0;
		}))
	{
		throw Exception("Some extension are not supported");
	}

	// create instance
	auto appInfo = Vulkan::Initializers::applicationInfo("VulkanApp",
		VulkanContext::m_appVersion, "VulkanEngine", VulkanContext::m_engineVersion,
		VK_API_VERSION_1_3);

	auto createInfo = Vulkan::Initializers::instanceCreateInfo(&appInfo);

	createInfo.enabledLayerCount = static_cast<uint32_t>(usedExtension.size());
	const auto vCharExt = vStringToChar(usedExtension);
	createInfo.ppEnabledExtensionNames = vCharExt.data();
	createInfo.enabledExtensionCount = static_cast<uint32_t>(a_param.layers.size());
	const auto vCharLayer = vStringToChar(a_param.layers);
	createInfo.ppEnabledLayerNames = vCharLayer.data();
	VK_CHECK_EXCEPT(vkCreateInstance(&createInfo, nullptr, &m_instance));
	m_capabilities = std::make_shared<VulkanCapabilities>(m_instance);

	if (a_param.bIsDebug)
	{
		auto vkCreateDebugUtilsMessengerEXT = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_instance, "vkCreateDebugUtilsMessengerEXT");
		if (vkCreateDebugUtilsMessengerEXT)
		{
			VkDebugUtilsMessengerCreateInfoEXT messCI = Vulkan::Initializers::messageCallbackCreateInfo();
			messCI.pUserData = this;
			messCI.pfnUserCallback = &VulkanContext::debugCallback;
			VK_CHECK_EXCEPT(vkCreateDebugUtilsMessengerEXT(m_instance, &messCI, nullptr, &m_debugMessenger));
		}
	}
}

VulkanContext::~VulkanContext()
{
	m_vDevices.clear();

	if (m_debugMessenger)
	{
		auto vkDestroyDebugUtilsMessengerEXT = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_instance, "vkDestroyDebugUtilsMessengerEXT");
		vkDestroyDebugUtilsMessengerEXT(m_instance, m_debugMessenger, nullptr);
	}

	if (m_instance)
	{
		vkDestroyInstance(m_instance, nullptr);
	}
}

bool VulkanContext::isValid()const noexcept
{
	return m_instance != VK_NULL_HANDLE;
}

VkSurfaceKHR VulkanContext::createSurface(void* a_platformWindow)const
{
	VkSurfaceKHR surface;
#if defined(WIN32)
	VkWin32SurfaceCreateInfoKHR surfaceCreateInfo = {};
	surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	surfaceCreateInfo.hinstance = (HINSTANCE)m_instance;
	surfaceCreateInfo.hwnd = (HWND)a_platformWindow;
	VK_CHECK_EXCEPT(vkCreateWin32SurfaceKHR(m_instance, &surfaceCreateInfo, nullptr, &surface));
#endif
	return surface;
}

VulkanDevicePtr VulkanContext::createNewDevice(const VulkanDeviceParameter& a_param, const DeviceChoice& a_choose, VkSurfaceKHR a_surface)
{
	VulkanDevicePtr vulkanDev;
	if (m_capabilities)
	{
		VulkanCapabilities::VulkanDeviceConfMap devMap;
		m_capabilities->findDeviceCompatibleConfiguration(a_param, devMap, a_surface);
		if (!devMap.empty())
		{
			auto iter = devMap.begin();
			
			if (devMap.size() > 1)
			{
				std::vector<int> vDeviceIndex;
				for (const auto& [id, conf] : devMap)
				{
					vDeviceIndex.emplace_back(id);
				}
				iter = devMap.find(a_choose(vDeviceIndex, this));
			}

			// because ctor is private
			vulkanDev = m_vDevices.emplace_back(std::shared_ptr<VulkanDevice>(new VulkanDevice(
				VulkanInstanceContext{.instanceHandle = m_instance},
				iter->first,
				iter->second,
				a_param
				)));
		}
	}
	return vulkanDev;
}


