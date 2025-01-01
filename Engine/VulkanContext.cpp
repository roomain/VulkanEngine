#include "pch.h"
#include <vector>
#include "VulkanContext.h"
#include "VulkanParameter.h"
#include "common/string_utils.h"
#include "common/contains.h"
#include "common/enumerate.h"
#include "VulkanDevice.h"
#include "VulkanSwapChain.h"
#include "VulkanInitializers.h"

#if defined(WIN32)
#include "vulkan/vulkan_win32.h"
#endif


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
	auto appInfo = Vulkan::Initializers::applicationInfo();
	appInfo.apiVersion = VK_VERSION_1_3; //VK_API_VERSION_1_0;// VK_VERSION_1_3;
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
	m_capabilities = std::make_shared<VulkanCapabilities>(m_instance);
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
			VkDevice logical;
			auto iter = devMap.begin();
			auto vExtents = vStringToChar(a_param.extensions);
			auto vLayers = vStringToChar(a_param.layers);
			auto features = VulkanDeviceCapabilities::toFeatures(a_param.features);

			if (devMap.size() > 1)
			{
				std::vector<int> vDeviceIndex;
				for (const auto& [id, conf] : devMap)
				{
					vDeviceIndex.emplace_back(id);
				}
				iter = devMap.find(a_choose(vDeviceIndex, this));
			}

			VkDeviceCreateInfo devInfo = Vulkan::Initializers::deviceCreateInfo();
			
			//set used queues
			devInfo.pQueueCreateInfos = iter->second.baseCreateInfo.data();
			devInfo.queueCreateInfoCount = static_cast<uint32_t>(iter->second.baseCreateInfo.size());

			devInfo.enabledExtensionCount = static_cast<uint32_t>(a_param.extensions.size());
			devInfo.ppEnabledExtensionNames = vExtents.data();
			devInfo.enabledLayerCount = static_cast<uint32_t>(a_param.layers.size());
			devInfo.ppEnabledLayerNames = vLayers.data();
			devInfo.pEnabledFeatures = &features;
			
			
			VK_CHECK_EXCEPT(vkCreateDevice(iter->second.physicalDev, &devInfo, nullptr, &logical))
			// because ctor is private
			vulkanDev = m_vDevices.emplace_back(std::shared_ptr<VulkanDevice>(new VulkanDevice(VulkanDeviceContext{
				m_instance,
				iter->first,
				iter->second.physicalDev, 
				logical 
				})));
		}
	}
	return vulkanDev;
}


