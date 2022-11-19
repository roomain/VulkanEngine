#include "pch.h"
#include "vk_Renderer.h"
#include "vk_logger.h"
#include "vk_WindowSystemProxy.h"
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
			pLogger->log(flags, objType, obj, location, code, layerPrefix, message);
		return VK_FALSE;
	}
	
	VK_Renderer::VK_Renderer()
	{
		//
	}

	VK_Renderer::~VK_Renderer()
	{
		release();
	}

	void VK_Renderer::init(const std::string& a_confFile, VK_Logger* const a_pLogger, const std::vector<std::string>& a_windowSysExtensions, std::vector<PhysicalDeviceInfo>& a_compatibleDevices)
	{
		loadConfiguration(a_confFile, m_vkConf);

		m_vkConf.instanceExtProps.insert(m_vkConf.instanceExtProps.end(), a_windowSysExtensions.begin(), a_windowSysExtensions.end());

		// check instance properties
		bool hasDebugExt = false;
		if (!checkInstanceExtensionProps(m_vkConf.instanceExtProps, hasDebugExt))
			throw Vulkan::VK_Exception("unsupported extensions", std::source_location::current());

		// check layers
		if (!checkInstanceLayerProps(m_vkConf.instanceLayers))
			throw Vulkan::VK_Exception("unsupported layers", std::source_location::current());

		// create vulkan instance
		createVulkanInstance(m_vkConf, m_vulkanInst);

		// create Debug
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

		int index = 0;
		uint32_t count = 0;
		vkEnumeratePhysicalDevices(m_vulkanInst, &count, nullptr);
		std::vector<VkPhysicalDevice> vDevices(count);
		vkEnumeratePhysicalDevices(m_vulkanInst, &count, vDevices.data());
		for (const auto& device : vDevices)
		{
			if (checkPhysicalDeviceExtension(device, m_vkConf.deviceExt) && checkPhysicalDeviceQueues(device, m_vkConf.queues))
			{
				VkPhysicalDeviceProperties devProp;
				vkGetPhysicalDeviceProperties(device, &devProp);
				a_compatibleDevices.emplace_back(PhysicalDeviceInfo{ index, devProp.deviceName });
			}
			++index;
		}
	}

	void VK_Renderer::startRendering(const unsigned int a_deviceIndex, std::unique_ptr<VK_WindowSystemProxy>&& a_windowProxy)
	{
		m_windowProxy = std::move(a_windowProxy);

		if (m_windowProxy)
		{
			uint32_t deviceCount = 0;
			vkEnumeratePhysicalDevices(m_vulkanInst, &deviceCount, nullptr);

			std::vector<VkPhysicalDevice> deviceList(deviceCount);
			vkEnumeratePhysicalDevices(m_vulkanInst, &deviceCount, deviceList.data());

			// choose physical device
			m_device.physical = deviceList[a_deviceIndex];

			// get queues configuration
			checkPhysicalDeviceQueues(m_device.physical, m_vkConf.queues);

			// create logical device
			createVulkanDevice(m_vkConf.queues, m_vkConf.deviceExt, m_device);

			// create swapchain
			VkSurfaceFormatKHR surfaceFormat;
			createSwapChain(m_device, m_swapChain, surfaceFormat, std::move(m_windowProxy));

			// get swap chain images
			uint32_t swapChainImageCount;
			vkGetSwapchainImagesKHR(m_device.logicalDevice, m_swapChain, &swapChainImageCount, nullptr);
			std::vector<VkImage> vImages(swapChainImageCount);
			vkGetSwapchainImagesKHR(m_device.logicalDevice, m_swapChain, &swapChainImageCount, vImages.data());

			// create images view from swapchain images
			for (const VkImage& img : vImages)
			{
				BaseImage swapChainImg{ .image = img };
				createSimpleImageView(m_device.logicalDevice, swapChainImg.image, surfaceFormat.format, VK_IMAGE_ASPECT_COLOR_BIT, swapChainImg.imageView);
				m_vSwapchainImages.emplace_back(swapChainImg);
			}

			// setup depth buffer
			
		}
		else
		{
			throw Vulkan::VK_Exception("Window proxy pointer is null.", std::source_location::current());
		}
	}

	void VK_Renderer::release()
	{
		if (m_debugCallbackHandle != VK_NULL_HANDLE)// optional
			vkDestroyDebugReportCallbackEXT(m_vulkanInst, m_debugCallbackHandle, nullptr);

		// release resources

		// destroy swapchain
		vkDestroySwapchainKHR(m_device.logicalDevice, m_swapChain, nullptr);

		// destroy logical device
		vkDestroyDevice(m_device.logicalDevice, nullptr);

		// destroy instance
		vkDestroyInstance(m_vulkanInst, nullptr);
	}


	VkInstance VK_Renderer::vulkanInstance()const noexcept
	{
		return m_vulkanInst;
	}

}