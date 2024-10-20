#include "pch.h"
#include "VulkanCapabilities.h"
#include "common/enumerate.h"
#include "VulkanInitializers.h"
#include "Vulkan_macros.h"


VulkanCapabilities::VulkanCapabilities()
{
	enumerate(&vkEnumerateInstanceExtensionProperties, m_extensions, nullptr);
	enumerate(&vkEnumerateInstanceLayerProperties, m_layers);

	auto instanceInfo = Vulkan::Initializers::instanceCreateInfo();
	VK_CHECK_EXCEPT(vkCreateInstance(&instanceInfo, nullptr, &m_instance));
	std::vector<VkPhysicalDevice> vDevices;
	enumerate(&vkEnumeratePhysicalDevices, vDevices, m_instance);
	int index = 0;
	for (const auto& physicalDev : vDevices)
	{
		m_devices.emplace_back(VulkanDeviceCapabilities(index ,physicalDev));
		++index;
	}
}

VulkanCapabilities::Extension_const_iterator VulkanCapabilities::extensionBegin()const noexcept
{
	return m_extensions.cbegin();
}

VulkanCapabilities::Extension_const_iterator VulkanCapabilities::extensionEnd()const noexcept
{
	return m_extensions.cend();
}

VulkanCapabilities::Layer_const_iterator VulkanCapabilities::layerBegin()const noexcept
{
	return m_layers.cbegin();
}

VulkanCapabilities::Layer_const_iterator VulkanCapabilities::layerEnd()const noexcept
{
	return m_layers.cend();
}

VulkanCapabilities::Device_const_iterator VulkanCapabilities::deviceBegin()const noexcept
{
	return m_devices.cbegin();
}

VulkanCapabilities::Device_const_iterator VulkanCapabilities::deviceEnd()const noexcept
{
	return m_devices.cend();
}