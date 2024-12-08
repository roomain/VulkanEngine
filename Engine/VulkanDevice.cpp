#include "pch.h"
#include "VulkanDevice.h"

VulkanDevice::VulkanDevice(const VulkanDeviceContext& a_context) : VulkanObject<VulkanDeviceContext>{ a_context }
{
	// todo
}

VulkanDevice::VulkanDevice(VulkanDeviceContext&& a_context) noexcept : VulkanObject<VulkanDeviceContext>{ a_context }
{
	// todo
}