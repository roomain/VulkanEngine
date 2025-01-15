#pragma once
/***********************************************
* @headerfile VulkanSwapChain.h
* @date 30 / 11 / 2024
* @author Roomain
************************************************/
#include <vulkan/vulkan.hpp>
#include "VulkanObject.h"
#include "common/notCopiable.h"
#include "VulkanLocalsContexts.h"

struct SwapChainBuffer
{
	VkImage image = VK_NULL_HANDLE;
	VkImageView imageView = VK_NULL_HANDLE;
};

class VulkanSwapChain : public VulkanObject<VulkanSwapChainContext>
{
	friend class VulkanDevice;
private:
	std::vector<SwapChainBuffer> m_buffer;			/*!< image buffer to display*/

#pragma region Internal
	/************************* creation functions*******************************************/
	[[nodiscard]] static VkExtent2D internal_computeImageExtent(const VkSurfaceCapabilitiesKHR& a_surfCaps, const uint32_t a_width, const uint32_t a_height);
	[[nodiscard]] static uint32_t internal_swapChainImageCount(const VkSurfaceCapabilitiesKHR& a_surfCaps);
	[[nodiscard]] static VkCompositeAlphaFlagBitsKHR internal_findCompositeAlpha(const VkSurfaceCapabilitiesKHR& a_surfCaps);
	[[nodiscard]] static VkSurfaceFormatKHR internal_findSurfaceFormat(const VulkanSwapChainContext& a_ctxt);
	void internal_releaseSwapchain(VkSwapchainKHR a_oldSwapChain);
	void internal_createBuffers(const VkFormat a_colorFormat);
	void internal_createSwapChain(const uint32_t a_width, const uint32_t a_height);
	/***************************************************************************************/
#pragma endregion

	VulkanSwapChain(const VulkanSwapChainContext& a_ctxt, const uint32_t a_width, const uint32_t a_height);

public:
	VulkanSwapChain() = delete;
	NOT_COPIABLE(VulkanSwapChain)
	virtual ~VulkanSwapChain();
	void reset(const uint32_t a_width, const uint32_t a_height);
	void acquireNextImage(VkSemaphore presentCompleteSemaphore, VkFence a_fence, uint32_t& a_imageIndex, SwapChainBuffer& a_image)const;
};