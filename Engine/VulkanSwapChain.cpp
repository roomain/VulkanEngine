#include "pch.h"
#include "VulkanSwapChain.h"
#include "Vulkan_macros.h"

VulkanSwapChain::VulkanSwapChain(const VulkanSwapChainContext& a_ctxt, VkSwapchainKHR a_swapChain) :
	VulkanObject<VulkanSwapChainContext>{ a_ctxt }, m_swapChain{ a_swapChain }
{
	//
}

VulkanSwapChain::~VulkanSwapChain()
{
	//
}

VkResult VulkanSwapChain::acquireNextImage(uint32_t& a_imageIndex, VkSemaphore presentCompleteSemaphore)
{
	//
}

void VulkanSwapChain::reset(const bool a_vSync, const bool a_fullScreen, const uint32_t a_width, const uint32_t a_height)
{
	//
}