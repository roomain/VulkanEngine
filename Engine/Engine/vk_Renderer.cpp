#include "pch.h"
#include "vk_Renderer.h"
#include "vk_logger.h"
#include "vk_WindowSystemProxy.h"
#include "vk_destroy.h"
#include <exception>
#include <algorithm>
#include <format>


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

	VK_Renderer::VK_Renderer() : m_swapChain{ VK_NULL_HANDLE }, m_graphicsQueue{ VK_NULL_HANDLE }, m_presentationQueue{ VK_NULL_HANDLE }, m_debugCallbackHandle{ VK_NULL_HANDLE }, m_renderingIndex{ 0 }
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
			if (checkPhysicalDeviceExtension(device, m_vkConf.deviceExt))
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
		m_renderingIndex = 0;
		if (m_windowProxy)
		{
			uint32_t deviceCount = 0;
			vkEnumeratePhysicalDevices(m_vulkanInst, &deviceCount, nullptr);

			std::vector<VkPhysicalDevice> deviceList(deviceCount);
			vkEnumeratePhysicalDevices(m_vulkanInst, &deviceCount, deviceList.data());

			// choose physical device
			m_device.physical = deviceList[a_deviceIndex];

			// get queues configuration
			checkPhysicalDeviceQueues(m_device.physical, m_windowProxy->surface(), m_vkConf.queues);

			// create logical device
			createVulkanDevice(m_vkConf.queues, m_vkConf.deviceExt, m_device);

			// create queues
			bool supportPresentation = false;
			int indexGraphics = m_vkConf.queues.queueVKIndex(VK_QUEUE_GRAPHICS_BIT, supportPresentation);
			vkGetDeviceQueue(m_device.logicalDevice, indexGraphics, 0, &m_graphicsQueue);
			if (supportPresentation)
			{
				m_presentationQueue = m_graphicsQueue;
			}
			else
			{
				int indexPresentation = m_vkConf.queues.presentationQueueVKIndex();
				vkGetDeviceQueue(m_device.logicalDevice, indexPresentation, 0, &m_presentationQueue);
			}

			// create swapchain
			VkSurfaceFormatKHR surfaceFormat;
			createSwapChain(m_device, m_swapChain, surfaceFormat, std::move(m_windowProxy), m_vSwapchainImages);
			resetSemaphores();

			// setup depth buffer
			if (m_vkConf.useDepthBuffer)
				createDepthBufferImages();
		}
		else
		{
			throw Vulkan::VK_Exception("Window proxy pointer is null.", std::source_location::current());
		}
	}

	void VK_Renderer::onWindowResized()
	{
		// Ensure all operations on the device have been finished before destroying resources
		vkDeviceWaitIdle(m_device.logicalDevice);


		// recreate swapchain
		VkSurfaceFormatKHR surfaceFormat;
		createSwapChain(m_device, m_swapChain, surfaceFormat, std::move(m_windowProxy), m_vSwapchainImages);
		resetSemaphores();

		// release and setup depth buffer
		if (m_vkConf.useDepthBuffer)
		{
			destroyDepthBufferImages();
			createDepthBufferImages();
		}

		// TODO
	}

	void VK_Renderer::destroySemaphores()
	{
		for (int i = 0; i < m_vAcquireSemaphore.size(); ++i)
		{
			vkDestroySemaphore(m_device.logicalDevice, m_vAcquireSemaphore[i], nullptr);
			vkDestroySemaphore(m_device.logicalDevice, m_vPresentSemaphore[i], nullptr);
		}

		m_vAcquireSemaphore.clear();
		m_vPresentSemaphore.clear();
	}

	void VK_Renderer::createSemaphores()
	{

		auto infoPresent = Initializers::semaphoreCreateInfo();
		auto infoAcquire = Initializers::semaphoreCreateInfo();

		for (int i = 0; i < m_vSwapchainImages.size(); ++i)
		{
			VkSemaphore presentSemaphore, acquireSemaphore;
			vkCreateSemaphore(m_device.logicalDevice, &infoPresent, nullptr, &presentSemaphore);
			vkCreateSemaphore(m_device.logicalDevice, &infoAcquire, nullptr, &acquireSemaphore);
			m_vPresentSemaphore.emplace_back(presentSemaphore);
			m_vAcquireSemaphore.emplace_back(acquireSemaphore);
		}
	}

	void VK_Renderer::resetSemaphores()
	{
		destroySemaphores();
		createSemaphores();
	}

	void VK_Renderer::release()
	{
		if (m_debugCallbackHandle != VK_NULL_HANDLE)// optional
			vkDestroyDebugReportCallbackEXT(m_vulkanInst, m_debugCallbackHandle, nullptr);
		m_debugCallbackHandle = VK_NULL_HANDLE;

		// release resources----------------------------------------------------		
		destoyPipelines();
		
		//----------------------------------------------------------------------

		// destroy command pool
		
		// destroy depth buffer
		if (m_vkConf.useDepthBuffer)
			destroyDepthBufferImages();

		// destroy swapchain
		destroySwapChain(m_device, m_swapChain, m_vSwapchainImages);
		
		destroySemaphores();

		// destoy surface
		vkDestroySurfaceKHR(m_vulkanInst, m_windowProxy->surface(), nullptr);
		m_windowProxy->resetSurface();

		// destroy logical device
		destroyVulkanDevice(m_device);

		// destroy instance
		destroyVulkanInstance(m_vulkanInst);
		m_renderingIndex = 0;
	}

	void VK_Renderer::destroyDepthBufferImages()
	{		
		destroyImagePool(m_device.logicalDevice, m_depthImagesPool);
	}

	void VK_Renderer::createDepthBufferImages()
	{
		VkFormat bestFormat = findBestImageFormat({ VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D32_SFLOAT, VK_FORMAT_D24_UNORM_S8_UINT },
			VK_IMAGE_TILING_OPTIMAL,
			VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);


		VkImageCreateInfo imageCreateInfo = {};
		imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		imageCreateInfo.imageType = VK_IMAGE_TYPE_2D;							// Type of image (1D, 2D, or 3D)
		imageCreateInfo.extent.width = m_windowProxy->width();					// Width of image extent
		imageCreateInfo.extent.height = m_windowProxy->height();				// Height of image extent
		imageCreateInfo.extent.depth = 1;										// Depth of image (just 1, no 3D aspect)
		imageCreateInfo.mipLevels = 1;											// Number of mipmap levels
		imageCreateInfo.arrayLayers = 1;										// Number of levels in image array
		imageCreateInfo.format = bestFormat;									// Format type of image
		imageCreateInfo.tiling = VK_IMAGE_TILING_OPTIMAL;						// How image data should be "tiled" (arranged for optimal reading)
		imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;				// Layout of image data on creation
		imageCreateInfo.usage = VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT;	// Bit flags defining what image will be used for
		imageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;						// Number of samples for multi-sampling
		imageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;				// Whether image can be shared between queues

		VkPhysicalDeviceMemoryProperties memoryProperties;
		vkGetPhysicalDeviceMemoryProperties(m_device.physical, &memoryProperties);
		createImagePool(m_device.logicalDevice, memoryProperties, static_cast<unsigned int >(m_vSwapchainImages.size()), imageCreateInfo, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_depthImagesPool);
	}

	VkFormat VK_Renderer::findBestImageFormat(const std::vector<VkFormat>& a_preferedFormats, const VkImageTiling a_preferedTiling, const VkFormatFeatureFlags a_preferedFlags)
	{
		for (VkFormat format : a_preferedFormats)
		{
			// Get properties for give format on this device
			VkFormatProperties properties;
			vkGetPhysicalDeviceFormatProperties(m_device.physical, format, &properties);

			// Depending on tiling choice, need to check for different bit flag
			if (a_preferedTiling == VK_IMAGE_TILING_LINEAR && (properties.linearTilingFeatures & a_preferedFlags) == a_preferedFlags)
			{
				return format;
			}
			else if (a_preferedTiling == VK_IMAGE_TILING_OPTIMAL && (properties.optimalTilingFeatures & a_preferedFlags) == a_preferedFlags)
			{
				return format;
			}
		}
		throw Vulkan::VK_Exception(std::format("Can't find any prefered format with tiling {} and flags {}", to_string(a_preferedTiling), Flag<VkFormatFeatureFlagBits>::to_string(a_preferedFlags)), std::source_location::current());
	}

	VkInstance VK_Renderer::vulkanInstance()const noexcept
	{
		return m_vulkanInst;
	}

	bool VK_Renderer::registerPipeline(VK_PipelinePtr& a_pipeline)
	{
		bool bRet = false;
		int index = 0;// index of pipelin with higher lower
		bool bFoundNext = false; // pipeline with lower priority is found;
		auto iter = std::find_if(m_PipelineList.begin(), m_PipelineList.end(), [&](const VK_PipelinePtr& a_iterPipeline)
			{
				if (a_iterPipeline->priority() < a_pipeline->priority() && !bFoundNext)
				{
					bFoundNext = true;
				}
				else
				{
					index++;
				}
				return a_iterPipeline == a_pipeline;
			});

		if (iter == m_PipelineList.end())
		{
			if (bFoundNext)
			{
				m_PipelineList.insert(m_PipelineList.begin() + index, a_pipeline);
			}
			else
			{
				m_PipelineList.push_back(a_pipeline);
			}
			bRet = true;
		}
		return bRet;
	}

	size_t VK_Renderer::pipelineCount()const noexcept
	{
		return m_PipelineList.size();
	}

	void VK_Renderer::releasePipeline(const size_t& a_index)
	{
		if (m_PipelineList.size() < a_index)
			m_PipelineList.erase(m_PipelineList.begin() + a_index);
	}

	void VK_Renderer::releasePipeline(VK_PipelinePtr& a_pipeline)
	{
		auto iter = std::find(m_PipelineList.begin(), m_PipelineList.end(), a_pipeline);
		if(iter != m_PipelineList.end())
			m_PipelineList.erase(iter);
	}

	void VK_Renderer::destoyPipelines()
	{
		for (auto pPipeline : m_PipelineList)
			pPipeline->destroy(m_device.logicalDevice);
		m_PipelineList.clear();
	}

	bool VK_Renderer::renderOnScreen()
	{
		bool bRet = false;

		// Get frame to render
		VkFence acquireFence;
		uint32_t frameIndex = 0;
		VkResult resAquire = vkAcquireNextImageKHR(m_device.logicalDevice, m_swapChain, m_vkConf.frameTimeout, m_vAcquireSemaphore[m_renderingIndex], acquireFence, &frameIndex);
		switch (resAquire)
		{
		case VK_SUCCESS:
		case VK_SUBOPTIMAL_KHR:
		{
			bRet = true;
			// TODO
			VkPresentInfoKHR presentation = Initializers::presentationKHR(1, &m_vPresentSemaphore[m_renderingIndex], 1, &m_swapChain, &frameIndex);
			vkQueuePresentKHR(m_graphicsQueue, &presentation);
		}
			break;
		default:
			break;
		}
		
		m_renderingIndex = (m_renderingIndex + 1) % static_cast<uint32_t>(m_vSwapchainImages.size());

		return bRet;
	}

	bool VK_Renderer::renderOffScreen()
	{
		bool bRet = false;
		//
		return bRet;
	}
}