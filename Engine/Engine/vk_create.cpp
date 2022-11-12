#include "pch.h"
#include "vk_WindowSystemProxy.h"

namespace Vulkan
{
	constexpr uint32_t ENGINE_VERSION = 1;								/*!< engine version*/

	void createVulkanInstance(const VulkanConfiguration& a_conf, VkInstance& a_vkInstance)
	{
		VkApplicationInfo appInfo = Vulkan::Initializers::applicationInfo();
		appInfo.apiVersion = VK_API_VERSION_1_3;
		appInfo.applicationVersion = a_conf.appVersion;
		appInfo.engineVersion = ENGINE_VERSION;
		appInfo.pApplicationName = a_conf.appName.c_str();
		appInfo.pEngineName = "VK_Engine";

		VkInstanceCreateInfo instCreateInfo = Vulkan::Initializers::instanceCreateInfo();
		instCreateInfo.pApplicationInfo = &appInfo;

		instCreateInfo.enabledExtensionCount = 0;
		instCreateInfo.ppEnabledExtensionNames = nullptr;

		instCreateInfo.enabledLayerCount = 0;
		instCreateInfo.ppEnabledLayerNames = nullptr;

		// generate table of char* from vectors of string
		size_t size = a_conf.instanceExtProps.size() + a_conf.instanceLayers.size();
		std::vector<const char*> vNameData;
		//const char** tabProp = new const char* [size];
		int iIndex = 0;
		for (auto& ext : a_conf.instanceExtProps)
			vNameData.emplace_back(ext.c_str());

		for (auto& layer : a_conf.instanceLayers)
			vNameData.emplace_back(layer.c_str());

		instCreateInfo.enabledExtensionCount = static_cast<uint32_t>(a_conf.instanceExtProps.size());
		instCreateInfo.ppEnabledExtensionNames = vNameData.data();

		instCreateInfo.enabledLayerCount = static_cast<uint32_t>(a_conf.instanceLayers.size());
		instCreateInfo.ppEnabledLayerNames = &vNameData[a_conf.instanceExtProps.size()];

		VK_CHECK(vkCreateInstance(&instCreateInfo, nullptr, &a_vkInstance));
	}

	void createVulkanDevice(const RendererQueuesConfiguration& a_queueConf, const std::vector<std::string>& a_deviceExt, Device& a_device)
	{
		// create queues create info for the device
		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::vector<float> vPriorities(a_queueConf.vQueueConf.size());
		std::fill(vPriorities.begin(), vPriorities.end(), 1.0f);

		int index = 0;
		for (const auto& conf : a_queueConf.vQueueConf)
		{
			auto createInfo = Initializers::queueCreateInfo();
			createInfo.queueCount = 1;
			createInfo.queueFamilyIndex = conf.index;
			createInfo.pQueuePriorities = &vPriorities[index];
			queueCreateInfos.emplace_back(std::move(createInfo));
			++index;
		}

		// info for create logical device
		VkDeviceCreateInfo deviceCreateInfo = Initializers::deviceCreateInfo();
		deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());		// Number of Queue Create Infos
		deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();								// List of queue create infos so device can create required queues
		deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(a_deviceExt.size());			// Number of enabled logical device extensions
		std::vector<const char*> vExtNames;
		for(const auto& name : a_deviceExt)
			vExtNames.emplace_back(name.c_str());
		
		deviceCreateInfo.ppEnabledExtensionNames = vExtNames.data();
		VK_CHECK(vkCreateDevice(a_device.physical, &deviceCreateInfo, nullptr, &a_device.logicalDevice))
	}

	void createSwapChain(const Device& a_device, VkSwapchainKHR& a_swapChain, VkSurfaceFormatKHR& a_surfaceFormat, std::unique_ptr<VK_WindowSystemProxy>&& a_windowProxy)
	{
		// Get swap chain capabilities
		SwapchainCapabilities swapChainCaps;
		getSwapChainCapabilities(a_device, a_windowProxy->surface(), swapChainCaps);

		// choose optimal surface values
		a_surfaceFormat = getBestSurfaceFormat(swapChainCaps.supportedFormats);
		VkPresentModeKHR presentMode = getBestPresentationMode(swapChainCaps.supportedModes);
		//VkExtent2D extent = chooseSwapExtent(swapChainDetails.surfaceCapabilities);

		// How many images are in the swap chain? Get 1 more than the minimum to allow triple buffering
		uint32_t imageCount = swapChainCaps.surfaceCapabilities.minImageCount + 1;

		// If imageCount higher than max, then clamp down to max
		// If 0, then limitless
		if (swapChainCaps.surfaceCapabilities.maxImageCount > 0 && swapChainCaps.surfaceCapabilities.maxImageCount < imageCount)
			imageCount = swapChainCaps.surfaceCapabilities.maxImageCount;
		
		// Creation information for swap chain
		VkSwapchainCreateInfoKHR swapChainCreateInfo = Vulkan::Initializers::swapChainCreateInfoKHR();
		swapChainCreateInfo.surface = a_windowProxy->surface();							// Swapchain surface
		swapChainCreateInfo.imageFormat = a_surfaceFormat.format;						// Swapchain format
		swapChainCreateInfo.imageColorSpace = a_surfaceFormat.colorSpace;				// Swapchain colour space
		swapChainCreateInfo.presentMode = presentMode;									// Swapchain presentation mode

		VkExtent2D newExtent = {};
		newExtent.width = a_windowProxy->width();
		newExtent.height = a_windowProxy->height();
		newExtent.width = std::clamp(newExtent.width, swapChainCaps.surfaceCapabilities.minImageExtent.width, swapChainCaps.surfaceCapabilities.maxImageExtent.width);
		newExtent.height = std::clamp(newExtent.height, swapChainCaps.surfaceCapabilities.minImageExtent.height, swapChainCaps.surfaceCapabilities.maxImageExtent.height);
		swapChainCreateInfo.imageExtent = newExtent;

		swapChainCreateInfo.minImageCount = imageCount;												// Minimum images in swapchain
		swapChainCreateInfo.imageArrayLayers = 1;													// Number of layers for each image in chain
		swapChainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;						// What attachment images will be used as
		swapChainCreateInfo.preTransform = swapChainCaps.surfaceCapabilities.currentTransform;		// Transform to perform on swap chain images
		swapChainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;						// How to handle blending images with external graphics (e.g. other windows)
		swapChainCreateInfo.clipped = VK_TRUE;														// Whether to clip parts of image not in view (e.g. behind another window, off screen, etc)

		VK_CHECK(vkCreateSwapchainKHR(a_device.logicalDevice, &swapChainCreateInfo, nullptr, &a_swapChain))

	}

	void createSimpleImageView(const VkDevice a_logicalDevice, const VkImage a_image, const VkFormat a_format, const VkImageAspectFlags a_aspectFlags, VkImageView& a_imgView)
	{
		VkImageViewCreateInfo viewCreateInfo = Vulkan::Initializers::imageViewCreateInfo();
		viewCreateInfo.image = a_image;											// Image to create view for
		viewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;						// Type of image (1D, 2D, 3D, Cube, etc)
		viewCreateInfo.format = a_format;										// Format of image data
		viewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;			// Allows remapping of rgba components to other rgba values
		viewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		viewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		viewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

		// Subresources allow the view to view only a part of an image
		viewCreateInfo.subresourceRange.aspectMask = a_aspectFlags;				// Which aspect of image to view (e.g. COLOR_BIT for viewing colour)
		viewCreateInfo.subresourceRange.baseMipLevel = 0;						// Start mipmap level to view from
		viewCreateInfo.subresourceRange.levelCount = 1;							// Number of mipmap levels to view
		viewCreateInfo.subresourceRange.baseArrayLayer = 0;						// Start array level to view from
		viewCreateInfo.subresourceRange.layerCount = 1;							// Number of array levels to view
		
		VK_CHECK(vkCreateImageView(a_logicalDevice, &viewCreateInfo, nullptr, &a_imgView))
	}
}