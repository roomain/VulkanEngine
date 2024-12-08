#pragma once
/***********************************************
* @headerfile VulkanSwapChain.h
* @date 30 / 11 / 2024
* @author Roomain
************************************************/
#include <vulkan/vulkan.hpp>
#include "common/notCopiable.h"

struct SwapChainBuffer
{
	VkImage image;
	VkImageView imageView;
};

class VulkanSwapChain
{
private:
	VkFormat colorFormat;
	VkColorSpaceKHR colorSpace;
	VkSwapchainKHR swapChain = VK_NULL_HANDLE;

	VulkanSwapChain(VkSwapchainKHR a_swapChain);

public:
	VulkanSwapChain() = delete;
	NOT_COPIABLE(VulkanSwapChain)
	virtual ~VulkanSwapChain();
	VkResult acquireNextImage(uint32_t& a_imageIndex, VkSemaphore presentCompleteSemaphore = VK_NULL_HANDLE);
	void reset(const bool a_vSync, const bool a_fullScreen, const uint32_t a_width, const uint32_t a_height);
};