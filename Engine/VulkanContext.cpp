#include "pch.h"
#include <vector>
#include "VulkanContext.h"
#include "VulkanParameter.h"
#include "common/string_utils.h"
#include "common/contains.h"
#include "common/enumerate.h"
#include "VulkanDevice.h"
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
	appInfo.apiVersion = VK_API_VERSION_1_0;// VK_VERSION_1_3;
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
					iter->second.physicalDev, 
					logical 
					})));
		}
	}
	return vulkanDev;
}

VkExtent2D VulkanContext::getCorrectedExtent(const VkSurfaceCapabilitiesKHR& surfCaps, uint32_t& a_width, uint32_t& a_height)
{
	VkExtent2D extent;
	if (surfCaps.currentExtent.width == (uint32_t)-1)
	{
		// If the surface size is undefined, the size is set to
		// the size of the images requested.
		extent.width = a_width;
		extent.height = a_height;
	}
	else
	{
		// If the surface size is defined, the swap chain size must match
		extent = surfCaps.currentExtent;
		a_width = surfCaps.currentExtent.width;
		a_height = surfCaps.currentExtent.height;
	}
	return extent;
}

uint32_t VulkanContext::getSwapChainImageCount(const VkSurfaceCapabilitiesKHR& surfCaps)
{
	uint32_t desiredNumberOfSwapchainImages = surfCaps.minImageCount + 1;
	if ((surfCaps.maxImageCount > 0) && (desiredNumberOfSwapchainImages > surfCaps.maxImageCount))
	{
		desiredNumberOfSwapchainImages = surfCaps.maxImageCount;
	}
	return desiredNumberOfSwapchainImages;
}

VkSwapchainKHR VulkanContext::createSwapChain(const VulkanSwapChainContext& a_ctxt, uint32_t& a_width, uint32_t& a_height, const VkSwapchainKHR a_oldSwpaChain)const
{
	// Get physical device surface properties and formats
	VkSurfaceCapabilitiesKHR surfCaps;
	VK_CHECK_EXCEPT(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(a_ctxt.physicalDevice, a_ctxt.surface, &surfCaps));
	
	std::vector<VkPresentModeKHR> presentationModes;
	enumerate(&vkGetPhysicalDeviceSurfacePresentModesKHR, presentationModes, a_ctxt.physicalDevice, a_ctxt.surface);
	
	// get image extents
	const VkExtent2D swapchainExtent = getCorrectedExtent(surfCaps, a_width, a_height);

	// Determine the number of images in swapchain
	const uint32_t desiredNumberOfSwapchainImages = getSwapChainImageCount(surfCaps);

	// Find the transformation of the surface
	VkSurfaceTransformFlagsKHR preTransform;
	if (surfCaps.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR)
	{
		// We prefer a non-rotated transform
		preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
	}
	else
	{
		preTransform = surfCaps.currentTransform;
	}

	// Find a supported composite alpha format (not all devices support alpha opaque)
	VkCompositeAlphaFlagBitsKHR compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	static constexpr std::array<VkCompositeAlphaFlagBitsKHR, 4>  compositeAlphaFlags = {
		VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
		VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR,
		VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR,
		VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR,
	};

	for (const auto& compositeAlphaFlag : compositeAlphaFlags) {
		if (surfCaps.supportedCompositeAlpha & compositeAlphaFlag) {
			compositeAlpha = compositeAlphaFlag;
			break;
		}
	}

	// The VK_PRESENT_MODE_FIFO_KHR mode must always be present as per spec
	// This mode waits for the vertical blank ("v-sync")
	VkPresentModeKHR swapchainPresentMode = VK_PRESENT_MODE_FIFO_KHR;

	VkSwapchainCreateInfoKHR swapchainCI = {};
	swapchainCI.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	swapchainCI.surface = a_ctxt.surface;
	swapchainCI.minImageCount = desiredNumberOfSwapchainImages;
	swapchainCI.imageFormat = colorFormat;
	swapchainCI.imageColorSpace = colorSpace;
	swapchainCI.imageExtent = { swapchainExtent.width, swapchainExtent.height };
	swapchainCI.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	swapchainCI.preTransform = (VkSurfaceTransformFlagBitsKHR)preTransform;
	swapchainCI.imageArrayLayers = 1;
	swapchainCI.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	swapchainCI.queueFamilyIndexCount = 0;
	swapchainCI.presentMode = swapchainPresentMode;
	// Setting oldSwapChain to the saved handle of the previous swapchain aids in resource reuse and makes sure that we can still present already acquired images
	swapchainCI.oldSwapchain = a_oldSwpaChain;
	// Setting clipped to VK_TRUE allows the implementation to discard rendering outside of the surface area
	swapchainCI.clipped = VK_TRUE;
	swapchainCI.compositeAlpha = compositeAlpha;

	// Enable transfer source on swap chain images if supported
	if (surfCaps.supportedUsageFlags & VK_IMAGE_USAGE_TRANSFER_SRC_BIT) {
		swapchainCI.imageUsage |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
	}
}