#include "pch.h"
#include <ranges>
#include "VulkanSwapChain.h"
#include "Vulkan_macros.h"
#include "common/enumerate.h"


#pragma region Internal
VkExtent2D VulkanSwapChain::internal_computeImageExtent(const VkSurfaceCapabilitiesKHR& a_surfCaps, const uint32_t a_width, const uint32_t a_height)
{
	VkExtent2D extent = a_surfCaps.currentExtent;
	if (a_surfCaps.currentExtent.width == (uint32_t)-1)
	{
		// If the surface size is undefined, the size is set to
		// the size of the images requested.
		extent.width = a_width;
		extent.height = a_height;
	}
	return extent;
}

uint32_t VulkanSwapChain::internal_swapChainImageCount(const VkSurfaceCapabilitiesKHR& a_surfCaps)
{
	uint32_t desiredNumberOfSwapchainImages = a_surfCaps.minImageCount + 1;
	if ((a_surfCaps.maxImageCount > 0) && (desiredNumberOfSwapchainImages > a_surfCaps.maxImageCount))
	{
		desiredNumberOfSwapchainImages = a_surfCaps.maxImageCount;
	}
	return desiredNumberOfSwapchainImages;
}

void VulkanSwapChain::internal_releaseSwapchain(VkSwapchainKHR a_oldSwapChain)
{
	for (const auto& img : m_SwapChainsBuffers)
		vkDestroyImageView(m_ctxt.logicalDevice, img.imageView, nullptr);
	vkDestroySwapchainKHR(m_ctxt.logicalDevice, a_oldSwapChain, nullptr);
	m_SwapChainsBuffers.clear();
}

VkSurfaceFormatKHR VulkanSwapChain::internal_findSurfaceFormat(const VulkanSwapChainContext& a_ctxt)
{
	std::vector<VkSurfaceFormatKHR> surfaceFormats;
	enumerate(&vkGetPhysicalDeviceSurfaceFormatsKHR, surfaceFormats, a_ctxt.physicalDevice, a_ctxt.surface);

	VkSurfaceFormatKHR surfaceFormat = surfaceFormats[0];

	// format un preferential order
	const std::vector<VkFormat> preferredImageFormats = {
		VK_FORMAT_R8G8B8A8_UNORM,
		VK_FORMAT_B8G8R8A8_UNORM,
		VK_FORMAT_A8B8G8R8_UNORM_PACK32
	};

	// find compatible format
	for (const auto& availableFormat : surfaceFormats) {
		if (std::ranges::find(preferredImageFormats, availableFormat.format) != preferredImageFormats.end()) {
			surfaceFormat = availableFormat;
			break;
		}
	}

	return surfaceFormat;
}

VkCompositeAlphaFlagBitsKHR VulkanSwapChain::internal_findCompositeAlpha(const VkSurfaceCapabilitiesKHR& a_surfCaps)
{
	VkCompositeAlphaFlagBitsKHR compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	static constexpr std::array<VkCompositeAlphaFlagBitsKHR, 4>  compositeAlphaFlags = {
		VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
		VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR,
		VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR,
		VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR,
	};

	for (const auto& compositeAlphaFlag : compositeAlphaFlags) {
		if (a_surfCaps.supportedCompositeAlpha & compositeAlphaFlag) {
			compositeAlpha = compositeAlphaFlag;
			break;
		}
	}

	return compositeAlpha;
}

void VulkanSwapChain::internal_createBuffers(const VkFormat a_colorFormat)
{
	uint32_t imageCount;
	std::vector<VkImage> images;
	VK_CHECK_EXCEPT(vkGetSwapchainImagesKHR(m_ctxt.logicalDevice, m_ctxt.swapChain, &imageCount, NULL));

	// Get the swap chain images
	images.resize(imageCount);
	VK_CHECK_EXCEPT(vkGetSwapchainImagesKHR(m_ctxt.logicalDevice, m_ctxt.swapChain, &imageCount, images.data()));

	for (const VkImage img : images)
	{
		VkImageView imageView = VK_NULL_HANDLE;


		VkImageViewCreateInfo colorAttachmentView = Vulkan::Initializers::imageViewCreateInfo(a_colorFormat, img, VK_IMAGE_VIEW_TYPE_2D, 0,
			VkImageSubresourceRange{
				.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
				.baseMipLevel = 0,
				.levelCount = 1,
				.baseArrayLayer = 0,
				.layerCount = 1
			});


		VK_CHECK_EXCEPT(vkCreateImageView(m_ctxt.logicalDevice, &colorAttachmentView, nullptr, &imageView))

		m_SwapChainsBuffers.emplace_back(SwapChainBuffer{
			img,
			imageView
			});
	}
}

void VulkanSwapChain::internal_createSwapChain(const uint32_t a_width, const uint32_t a_height)
{
	// Get physical device surface properties and formats
	VkSurfaceCapabilitiesKHR surfCaps;
	VK_CHECK_EXCEPT(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_ctxt.physicalDevice, m_ctxt.surface, &surfCaps))

	std::vector<VkPresentModeKHR> presentationModes;
	enumerate(&vkGetPhysicalDeviceSurfacePresentModesKHR, presentationModes, m_ctxt.physicalDevice, m_ctxt.surface);

	const VkExtent2D swapchainExtent = internal_computeImageExtent(surfCaps, a_width, a_height);

	// Determine the number of images in swapchain
	const uint32_t desiredNumberOfSwapchainImages = internal_swapChainImageCount(surfCaps);


	// The VK_PRESENT_MODE_FIFO_KHR mode must always be present as per spec
	// This mode waits for the vertical blank ("v-sync")
	VkPresentModeKHR swapchainPresentMode = VK_PRESENT_MODE_FIFO_KHR;
	VkSurfaceFormatKHR imageFormat = VulkanSwapChain::internal_findSurfaceFormat(m_ctxt);

	VkImageUsageFlags usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | surfCaps.supportedUsageFlags;
	VkSwapchainCreateInfoKHR swapchainCI = Vulkan::Initializers::swapChainCreateInfoKHR(m_ctxt.surface, imageFormat,
		desiredNumberOfSwapchainImages, swapchainExtent, usage, surfCaps.currentTransform, VulkanSwapChain::internal_findCompositeAlpha(surfCaps), swapchainPresentMode, VK_TRUE, m_ctxt.swapChain);


	VK_CHECK_EXCEPT(vkCreateSwapchainKHR(m_ctxt.logicalDevice, &swapchainCI, nullptr, &m_ctxt.swapChain))

		if (swapchainCI.oldSwapchain != VK_NULL_HANDLE)
		{
			internal_releaseSwapchain(swapchainCI.oldSwapchain);
		}

	internal_createBuffers(imageFormat.format);
}
#pragma endregion


VulkanSwapChain::VulkanSwapChain(const VulkanSwapChainContext& a_ctxt, const uint32_t a_width, const uint32_t a_height) :
	VulkanObject<VulkanSwapChainContext>{ a_ctxt }
{
	internal_createSwapChain(a_width, a_height);
}

VulkanSwapChain::~VulkanSwapChain()
{
	internal_releaseSwapchain(m_ctxt.swapChain);
}

void VulkanSwapChain::reset(const uint32_t a_width, const uint32_t a_height)
{
	internal_createSwapChain(a_width, a_height);
}

void VulkanSwapChain::acquireNextImage(VkSemaphore presentCompleteSemaphore, VkFence a_fence, uint32_t& a_imageIndex, SwapChainBuffer& a_image)const
{
	VK_CHECK_LOG(vkAcquireNextImageKHR(m_ctxt.logicalDevice, m_ctxt.swapChain, UINT64_MAX, presentCompleteSemaphore, a_fence, &a_imageIndex))
		a_image = m_SwapChainsBuffers[a_imageIndex];
}

void VulkanSwapChain::present(VkQueue a_presentationQueue, const uint32_t a_imageIndex, VkSemaphore a_waitSemaphore)const
{
	auto presentCI = Vulkan::Initializers::presentationKHR(1, &a_waitSemaphore, 1, &m_ctxt.swapChain, &a_imageIndex);
	VK_CHECK_LOG(vkQueuePresentKHR(a_presentationQueue, &presentCI))
}

void VulkanSwapChain::present(VkQueue a_presentationQueue, const uint32_t a_imageIndex, std::vector<VkSemaphore>& a_waitSemaphore)const
{
	auto presentCI = Vulkan::Initializers::presentationKHR(static_cast<uint32_t>(a_waitSemaphore.size()),
		a_waitSemaphore.data(), 1, &m_ctxt.swapChain, &a_imageIndex);
	VK_CHECK_LOG(vkQueuePresentKHR(a_presentationQueue, &presentCI))
}
