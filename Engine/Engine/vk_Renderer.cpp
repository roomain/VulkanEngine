#include "pch.h"
#include "vk_Renderer.h"
#include "vk_logger.h"
#include "vk_WindowSystemProxy.h"
#include <exception>
#include <algorithm>
#include <format>


namespace Vulkan
{
	void VK_Renderer::createSwapChain()
	{
		// Get swap chain capabilities
		const SwapchainCapabilities& swapChainCaps = VK_VulkanCapabilities::instance()[m_vkDevice.deviceIndex].swapchainCapabilities();
		// choose optimal surface values
		VkSurfaceFormatKHR surfaceFormat = VK_VulkanCapabilities::instance()[m_vkDevice.deviceIndex].bestSurfaceFormat();
		VkPresentModeKHR presentMode = VK_VulkanCapabilities::instance()[m_vkDevice.deviceIndex].bestPresentationMode();

		// How many images are in the swap chain? Get 1 more than the minimum to allow triple buffering
		uint32_t imageCount = swapChainCaps.surfaceCapabilities.minImageCount + 1;

		// If imageCount higher than max, then clamp down to max
		// If 0, then limitless
		if (swapChainCaps.surfaceCapabilities.maxImageCount > 0 && swapChainCaps.surfaceCapabilities.maxImageCount < imageCount)
			imageCount = swapChainCaps.surfaceCapabilities.maxImageCount;

		// Creation information for swap chain
		VkSwapchainCreateInfoKHR swapChainCreateInfo = Vulkan::Initializers::swapChainCreateInfoKHR();
		swapChainCreateInfo.surface = m_pWindowProxy->surface();					// Swapchain surface
		swapChainCreateInfo.imageFormat = surfaceFormat.format;						// Swapchain format
		swapChainCreateInfo.imageColorSpace = surfaceFormat.colorSpace;				// Swapchain colour space
		swapChainCreateInfo.presentMode = presentMode;								// Swapchain presentation mode

		VkExtent2D newExtent = {};
		newExtent.width = m_pWindowProxy->width();
		newExtent.height = m_pWindowProxy->height();
		newExtent.width = std::clamp(newExtent.width, swapChainCaps.surfaceCapabilities.minImageExtent.width, swapChainCaps.surfaceCapabilities.maxImageExtent.width);
		newExtent.height = std::clamp(newExtent.height, swapChainCaps.surfaceCapabilities.minImageExtent.height, swapChainCaps.surfaceCapabilities.maxImageExtent.height);
		swapChainCreateInfo.imageExtent = newExtent;

		swapChainCreateInfo.minImageCount = imageCount;												// Minimum images in swapchain
		swapChainCreateInfo.imageArrayLayers = 1;													// Number of layers for each image in chain
		swapChainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;						// What attachment images will be used as
		swapChainCreateInfo.preTransform = swapChainCaps.surfaceCapabilities.currentTransform;		// Transform to perform on swap chain images
		swapChainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;						// How to handle blending images with external graphics (e.g. other windows)
		swapChainCreateInfo.clipped = VK_TRUE;														// Whether to clip parts of image not in view (e.g. behind another window, off screen, etc)
		VkSwapchainKHR oldSwapChain = m_swapChain;
		swapChainCreateInfo.oldSwapchain = oldSwapChain;
		VK_CHECK(vkCreateSwapchainKHR(m_vkDevice.logicalDevice, &swapChainCreateInfo, nullptr, &m_swapChain))

			if (oldSwapChain != VK_NULL_HANDLE)
				destroySwapChain();

		// get swap chain images
		uint32_t swapChainImageCount;
		vkGetSwapchainImagesKHR(m_vkDevice.logicalDevice, m_swapChain, &swapChainImageCount, nullptr);
		std::vector<VkImage> vImages(swapChainImageCount);
		vkGetSwapchainImagesKHR(m_vkDevice.logicalDevice, m_swapChain, &swapChainImageCount, vImages.data());

		// create images view from swapchain images
		for (const VkImage& img : vImages)
		{
			BaseImage swapChainImg{ .image = img };
			createImageView(swapChainImg.image, surfaceFormat.format, VK_IMAGE_ASPECT_COLOR_BIT, swapChainImg.imageView);
			m_vSwapchainImages.emplace_back(swapChainImg);
		}
	}

	void VK_Renderer::destroySwapChain()
	{
		// destroy color image
		for (const auto& image : m_vSwapchainImages)
			vkDestroyImageView(m_vkDevice.logicalDevice, image.imageView, nullptr);

		// destroy depth buffer
		for (auto& imageStruct : m_depthImagesPool.images)
		{
			vkDestroyImageView(m_vkDevice.logicalDevice, imageStruct.imageView, nullptr);
			vkDestroyImage(m_vkDevice.logicalDevice, imageStruct.image, nullptr);
		}
		vkFreeMemory(m_vkDevice.logicalDevice, m_depthImagesPool.memory, nullptr);

	

		vkDestroySwapchainKHR(m_vkDevice.logicalDevice, m_swapChain, nullptr);
		m_vSwapchainImages.clear();
	}

	VK_Renderer::VK_Renderer(const uint32_t a_deviceIndex, RenderDeviceConf&& a_rendererConf,
		const std::vector<std::string>& a_deviceExt, const std::shared_ptr<VK_WindowSystemProxy>& a_pWwinProxy) : VK_Device{ a_deviceIndex },
		m_RendererConf{std::move(a_rendererConf)},
		m_swapChain { VK_NULL_HANDLE }, m_graphicsQueue{ VK_NULL_HANDLE }, m_presentationQueue{ VK_NULL_HANDLE }, m_renderingIndex{ 0 },
		m_pWindowProxy{ a_pWwinProxy }, m_acquireFence{ VK_NULL_HANDLE }
	{
		// create logical device
		VK_Device::createLogicalDevice(m_RendererConf.queueConf, a_deviceExt, m_vkDevice);

		if (m_pWindowProxy)
		{
			// create swapchain
			createSwapChain();
			resetSemaphores();

			if (m_acquireFence == VK_NULL_HANDLE)
			{
				// create acquire fence
				VkFenceCreateInfo fenceCreate = Initializers::fenceCreateInfo();
				vkCreateFence(m_vkDevice.logicalDevice, &fenceCreate, nullptr, &m_acquireFence);
			}

			// setup depth buffer
			if (m_RendererConf.useDepthBuffer)
				createDepthBufferImages();
		}
		else
		{
			throw Vulkan::VK_Exception("Window proxy pointer is null.", std::source_location::current());
		}
	}

	VK_Renderer::~VK_Renderer()
	{
		release();
	}

	void VK_Renderer::onWindowResized()
	{
		// Ensure all operations on the device have been finished before destroying resources
		vkDeviceWaitIdle(m_vkDevice.logicalDevice);


		// recreate swapchain
		createSwapChain();
		resetSemaphores();

		// release and setup depth buffer
		if (m_RendererConf.useDepthBuffer)
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
			vkDestroySemaphore(m_vkDevice.logicalDevice, m_vAcquireSemaphore[i], nullptr);
			vkDestroySemaphore(m_vkDevice.logicalDevice, m_vPresentSemaphore[i], nullptr);
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
			vkCreateSemaphore(m_vkDevice.logicalDevice, &infoPresent, nullptr, &presentSemaphore);
			vkCreateSemaphore(m_vkDevice.logicalDevice, &infoAcquire, nullptr, &acquireSemaphore);
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
		vkDeviceWaitIdle(m_vkDevice.logicalDevice);
		//----------------------------------------------------------------------
		//destoy fences
		if (m_acquireFence != VK_NULL_HANDLE)
			vkDestroyFence(m_vkDevice.logicalDevice, m_acquireFence, nullptr);

		// destroy command pool
		
		// destroy depth buffer
		if (m_RendererConf.useDepthBuffer)
			destroyDepthBufferImages();

		// destroy swapchain
		destroySwapChain();
		
		destroySemaphores();

		// destoy surface
		vkDestroySurfaceKHR(m_RendererConf.vkInstance, m_pWindowProxy->surface(), nullptr);
		m_pWindowProxy->resetSurface();
		m_renderingIndex = 0;
	}

	void VK_Renderer::destroyDepthBufferImages()
	{		
		destroyImagePool(m_depthImagesPool);
	}

	void VK_Renderer::createDepthBufferImages()
	{
		VkFormat bestFormat = findBestImageFormat({ VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D32_SFLOAT, VK_FORMAT_D24_UNORM_S8_UINT },
			VK_IMAGE_TILING_OPTIMAL,
			VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);

		MemorySameImagePoolConf memConf;
		memConf.imageCount = static_cast<unsigned int>(m_vSwapchainImages.size());
		memConf.imageCreateInfo = Vulkan::Initializers::imageCreateInfo();
		memConf.imageCreateInfo.imageType = VK_IMAGE_TYPE_2D;							// Type of image (1D, 2D, or 3D)
		memConf.imageCreateInfo.extent.width = m_pWindowProxy->width();					// Width of image extent
		memConf.imageCreateInfo.extent.height = m_pWindowProxy->height();				// Height of image extent
		memConf.imageCreateInfo.extent.depth = 1;										// Depth of image (just 1, no 3D aspect)
		memConf.imageCreateInfo.mipLevels = 1;											// Number of mipmap levels
		memConf.imageCreateInfo.arrayLayers = 1;										// Number of levels in image array
		memConf.imageCreateInfo.format = bestFormat;									// Format type of image
		memConf.imageCreateInfo.tiling = VK_IMAGE_TILING_OPTIMAL;						// How image data should be "tiled" (arranged for optimal reading)
		memConf.imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;				// Layout of image data on creation
		memConf.imageCreateInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT;	// Bit flags defining what image will be used for
		memConf.imageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;						// Number of samples for multi-sampling
		memConf.imageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;				// Whether image can be shared between queues
		memConf.memProps = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
		createImagePool(memConf, m_depthImagesPool);

		// create image view
		for(auto& imageStruct  : m_depthImagesPool.images)
			createImageView(imageStruct.image, bestFormat, VK_IMAGE_ASPECT_DEPTH_BIT, imageStruct.imageView);
	}

	VkFormat VK_Renderer::findBestImageFormat(const std::vector<VkFormat>& a_preferedFormats, const VkImageTiling a_preferedTiling, const VkFormatFeatureFlags a_preferedFlags)
	{
		for (VkFormat format : a_preferedFormats)
		{
			// Get properties for give format on this device
			VkFormatProperties properties;
			vkGetPhysicalDeviceFormatProperties(m_vkDevice.physical, format, &properties);

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
	
	bool VK_Renderer::renderOnScreen()
	{
		bool bRet = false;


		// Get frame to render
		uint32_t frameIndex = 0;
		VkResult resAquire = vkAcquireNextImageKHR(m_vkDevice.logicalDevice, m_swapChain, m_RendererConf.frameTimeout, m_vAcquireSemaphore[m_renderingIndex], m_acquireFence, &frameIndex);
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