#include "pch.h"
#include "VulkanDevice.h"
#include "VulkanSwapChain.h"

VulkanDevice::VulkanDevice(const VulkanDeviceContext& a_context) : VulkanObject<VulkanDeviceContext>{ a_context }, 
m_deviceCapabilities{ static_cast<uint32_t>(a_context.deviceIndex), a_context.physicalDevice }
{
}

VulkanDevice::VulkanDevice(VulkanDeviceContext&& a_context) noexcept : VulkanObject<VulkanDeviceContext>{ a_context },
m_deviceCapabilities{ static_cast<uint32_t>(a_context.deviceIndex), a_context.physicalDevice }
{
}

VulkanSwapChainPtr VulkanDevice::createNewSwapChain(const VulkanDeviceContext& a_devCtxt, VkSurfaceKHR a_surface, const uint32_t a_width, const uint32_t a_height)
{
	const VulkanSwapChainContext context{ a_devCtxt,  a_surface };
	// because ctor is private
	m_deviceSwapChain =  std::shared_ptr<VulkanSwapChain>(new VulkanSwapChain(context, a_width, a_height));
	return m_deviceSwapChain;
}

VulkanSwapChainPtr VulkanDevice::swapChain()const
{
	return m_deviceSwapChain;
}