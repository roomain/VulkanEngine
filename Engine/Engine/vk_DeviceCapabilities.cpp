#include "pch.h"
#include "vk_DeviceCapabilities.h"
#include "VK_WindowSystemProxy.h"
#include "IDataDisplayer.h"

namespace Vulkan
{

	void VK_DeviceCapabilities::getFormatsProperties()
	{
		FormatProperty formatProp = { .format = VK_FORMAT_R4G4_UNORM_PACK8 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R4G4B4A4_UNORM_PACK16 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B4G4R4A4_UNORM_PACK16 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R5G6B5_UNORM_PACK16 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B5G6R5_UNORM_PACK16 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R5G5B5A1_UNORM_PACK16 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B5G5R5A1_UNORM_PACK16 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A1R5G5B5_UNORM_PACK16 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8_UNORM };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8_SNORM };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8_USCALED };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8_SSCALED };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8_UINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8_SINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8_SRGB };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8_UNORM };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8_SNORM };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8_USCALED };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8_SSCALED };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8_UINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8_SINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8_SRGB };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8B8_UNORM };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8B8_SNORM };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8B8_USCALED };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8B8_SSCALED };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8B8_UINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8B8_SINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8B8_SRGB };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B8G8R8_UNORM };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B8G8R8_SNORM };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B8G8R8_USCALED };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B8G8R8_SSCALED };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B8G8R8_UINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B8G8R8_SINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B8G8R8_SRGB };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8B8A8_UNORM };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8B8A8_SNORM };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8B8A8_USCALED };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8B8A8_SSCALED };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8B8A8_UINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8B8A8_SINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8B8A8_SRGB };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B8G8R8A8_UNORM };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B8G8R8A8_SNORM };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B8G8R8A8_USCALED };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B8G8R8A8_SSCALED };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B8G8R8A8_UINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B8G8R8A8_SINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B8G8R8A8_SRGB };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A8B8G8R8_UNORM_PACK32 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A8B8G8R8_SNORM_PACK32 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A8B8G8R8_USCALED_PACK32 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A8B8G8R8_SSCALED_PACK32 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A8B8G8R8_UINT_PACK32 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A8B8G8R8_SINT_PACK32 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A8B8G8R8_SRGB_PACK32 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A2R10G10B10_UNORM_PACK32 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A2R10G10B10_SNORM_PACK32 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A2R10G10B10_USCALED_PACK32 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A2R10G10B10_SSCALED_PACK32 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A2R10G10B10_UINT_PACK32 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A2R10G10B10_SINT_PACK32 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A2B10G10R10_UNORM_PACK32 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A2B10G10R10_SNORM_PACK32 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A2B10G10R10_USCALED_PACK32 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A2B10G10R10_SSCALED_PACK32 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A2B10G10R10_UINT_PACK32 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A2B10G10R10_SINT_PACK32 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16_UNORM };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16_SNORM };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16_USCALED };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16_SSCALED };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16_UINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16_SINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16_SFLOAT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16_UNORM };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16_SNORM };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16_USCALED };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16_SSCALED };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16_UINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16_SINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16_SFLOAT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16B16_UNORM };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16B16_SNORM };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16B16_USCALED };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16B16_SSCALED };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16B16_UINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16B16_SINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16B16_SFLOAT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16B16A16_UNORM };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16B16A16_SNORM };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16B16A16_USCALED };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16B16A16_SSCALED };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16B16A16_UINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16B16A16_SINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16B16A16_SFLOAT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R32_UINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R32_SINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R32_SFLOAT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R32G32_UINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R32G32_SINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R32G32_SFLOAT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R32G32B32_UINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R32G32B32_SINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R32G32B32_SFLOAT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R32G32B32A32_UINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R32G32B32A32_SINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R32G32B32A32_SFLOAT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R64_UINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R64_SINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R64_SFLOAT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R64G64_UINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R64G64_SINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R64G64_SFLOAT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R64G64B64_UINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R64G64B64_SINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R64G64B64_SFLOAT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R64G64B64A64_UINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R64G64B64A64_SINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R64G64B64A64_SFLOAT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B10G11R11_UFLOAT_PACK32 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_E5B9G9R9_UFLOAT_PACK32 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_D16_UNORM };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_X8_D24_UNORM_PACK32 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_D32_SFLOAT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_S8_UINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_D16_UNORM_S8_UINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_D24_UNORM_S8_UINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_D32_SFLOAT_S8_UINT };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_BC1_RGB_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_BC1_RGB_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_BC1_RGBA_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_BC1_RGBA_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_BC2_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_BC2_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_BC3_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_BC3_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_BC4_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_BC4_SNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_BC5_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_BC5_SNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_BC6H_UFLOAT_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_BC6H_SFLOAT_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_BC7_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_BC7_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_EAC_R11_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_EAC_R11_SNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_EAC_R11G11_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_EAC_R11G11_SNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_4x4_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_4x4_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_5x4_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_5x4_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_5x5_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_5x5_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_6x5_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_6x5_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_6x6_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_6x6_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_8x5_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_8x5_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_8x6_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_8x6_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_8x8_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_8x8_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_10x5_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_10x5_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_10x6_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_10x6_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_10x8_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_10x8_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_10x10_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_10x10_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_12x10_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_12x10_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_12x12_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_12x12_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G8B8G8R8_422_UNORM };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B8G8R8G8_422_UNORM };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G8_B8R8_2PLANE_420_UNORM };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G8_B8R8_2PLANE_422_UNORM };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R10X6_UNORM_PACK16 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R10X6G10X6_UNORM_2PACK16 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R12X4_UNORM_PACK16 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R12X4G12X4_UNORM_2PACK16 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G16B16G16R16_422_UNORM };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B16G16R16G16_422_UNORM };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G16_B16R16_2PLANE_420_UNORM };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G16_B16R16_2PLANE_422_UNORM };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G8_B8R8_2PLANE_444_UNORM };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G10X6_B10X6R10X6_2PLANE_444_UNORM_3PACK16 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G12X4_B12X4R12X4_2PLANE_444_UNORM_3PACK16 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G16_B16R16_2PLANE_444_UNORM };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A4R4G4B4_UNORM_PACK16 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A4B4G4R4_UNORM_PACK16 };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_4x4_SFLOAT_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_5x4_SFLOAT_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_5x5_SFLOAT_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_6x5_SFLOAT_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_6x6_SFLOAT_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_8x5_SFLOAT_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_8x6_SFLOAT_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_8x8_SFLOAT_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_10x5_SFLOAT_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_10x6_SFLOAT_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_10x8_SFLOAT_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_10x10_SFLOAT_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_12x10_SFLOAT_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_12x12_SFLOAT_BLOCK };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_PVRTC1_4BPP_UNORM_BLOCK_IMG };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_PVRTC2_2BPP_UNORM_BLOCK_IMG };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_PVRTC2_4BPP_UNORM_BLOCK_IMG };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_PVRTC1_2BPP_SRGB_BLOCK_IMG };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_PVRTC1_4BPP_SRGB_BLOCK_IMG };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_PVRTC2_2BPP_SRGB_BLOCK_IMG };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_PVRTC2_4BPP_SRGB_BLOCK_IMG };
		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, formatProp.format, &formatProp.properties);
		m_formatsProperties.push_back(formatProp);

	}


	void VK_DeviceCapabilities::displayDeviceLimits(IDataDisplayer& a_displayer)const
	{
		a_displayer.beginNode("Physical Device limits");
		a_displayer.attribute("maxImageDimension1D", m_deviceProperties.limits.maxImageDimension1D);
		a_displayer.attribute("maxImageDimension2D", m_deviceProperties.limits.maxImageDimension2D);
		a_displayer.attribute("maxImageDimension3D", m_deviceProperties.limits.maxImageDimension3D);
		a_displayer.attribute("maxImageDimensionCube", m_deviceProperties.limits.maxImageDimensionCube);
		a_displayer.attribute("maxImageArrayLayers", m_deviceProperties.limits.maxImageArrayLayers);
		a_displayer.attribute("maxTexelBufferElements", m_deviceProperties.limits.maxTexelBufferElements);
		a_displayer.attribute("maxUniformBufferRange", m_deviceProperties.limits.maxUniformBufferRange);
		a_displayer.attribute("maxStorageBufferRange", m_deviceProperties.limits.maxStorageBufferRange);
		a_displayer.attribute("maxPushConstantsSize", m_deviceProperties.limits.maxPushConstantsSize);
		a_displayer.attribute("maxMemoryAllocationCount", m_deviceProperties.limits.maxMemoryAllocationCount);
		a_displayer.attribute("maxSamplerAllocationCount", m_deviceProperties.limits.maxSamplerAllocationCount);
		a_displayer.attribute("bufferImageGranularity", static_cast<size_t>(m_deviceProperties.limits.bufferImageGranularity));
		a_displayer.attribute("sparseAddressSpaceSize", static_cast<size_t>(m_deviceProperties.limits.sparseAddressSpaceSize));
		a_displayer.attribute("maxBoundDescriptorSets", m_deviceProperties.limits.maxBoundDescriptorSets);
		a_displayer.attribute("maxPerStageDescriptorSamplers", m_deviceProperties.limits.maxPerStageDescriptorSamplers);
		a_displayer.attribute("maxPerStageDescriptorUniformBuffers", m_deviceProperties.limits.maxPerStageDescriptorUniformBuffers);
		a_displayer.attribute("maxPerStageDescriptorStorageBuffers", m_deviceProperties.limits.maxPerStageDescriptorStorageBuffers);
		a_displayer.attribute("maxPerStageDescriptorSampledImages", m_deviceProperties.limits.maxPerStageDescriptorSampledImages);
		a_displayer.attribute("maxPerStageDescriptorStorageImages", m_deviceProperties.limits.maxPerStageDescriptorStorageImages);
		a_displayer.attribute("maxPerStageDescriptorInputAttachments", m_deviceProperties.limits.maxPerStageDescriptorInputAttachments);
		a_displayer.attribute("maxPerStageResources", m_deviceProperties.limits.maxPerStageResources);
		a_displayer.attribute("maxDescriptorSetSamplers", m_deviceProperties.limits.maxDescriptorSetSamplers);
		a_displayer.attribute("maxDescriptorSetUniformBuffers", m_deviceProperties.limits.maxDescriptorSetUniformBuffers);
		a_displayer.attribute("maxDescriptorSetUniformBuffersDynamic", m_deviceProperties.limits.maxDescriptorSetUniformBuffersDynamic);
		a_displayer.attribute("maxDescriptorSetStorageBuffers", m_deviceProperties.limits.maxDescriptorSetStorageBuffers);
		a_displayer.attribute("maxDescriptorSetStorageBuffersDynamic", m_deviceProperties.limits.maxDescriptorSetStorageBuffersDynamic);
		a_displayer.attribute("maxDescriptorSetSampledImages", m_deviceProperties.limits.maxDescriptorSetSampledImages);
		a_displayer.attribute("maxDescriptorSetStorageImages", m_deviceProperties.limits.maxDescriptorSetStorageImages);
		a_displayer.attribute("maxDescriptorSetInputAttachments", m_deviceProperties.limits.maxDescriptorSetInputAttachments);
		a_displayer.attribute("maxVertexInputAttributes", m_deviceProperties.limits.maxVertexInputAttributes);
		a_displayer.attribute("maxVertexInputBindings", m_deviceProperties.limits.maxVertexInputBindings);
		a_displayer.attribute("maxVertexInputAttributeOffset", m_deviceProperties.limits.maxVertexInputAttributeOffset);
		a_displayer.attribute("maxVertexInputBindingStride", m_deviceProperties.limits.maxVertexInputBindingStride);
		a_displayer.attribute("maxVertexOutputComponents", m_deviceProperties.limits.maxVertexOutputComponents);
		a_displayer.attribute("maxTessellationGenerationLevel", m_deviceProperties.limits.maxTessellationGenerationLevel);
		a_displayer.attribute("maxTessellationPatchSize", m_deviceProperties.limits.maxTessellationPatchSize);
		a_displayer.attribute("maxTessellationControlPerVertexInputComponents", m_deviceProperties.limits.maxTessellationControlPerVertexInputComponents);
		a_displayer.attribute("maxTessellationControlPerVertexOutputComponents", m_deviceProperties.limits.maxTessellationControlPerVertexOutputComponents);
		a_displayer.attribute("maxTessellationControlPerPatchOutputComponents", m_deviceProperties.limits.maxTessellationControlPerPatchOutputComponents);
		a_displayer.attribute("maxTessellationControlTotalOutputComponents", m_deviceProperties.limits.maxTessellationControlTotalOutputComponents);
		a_displayer.attribute("maxTessellationEvaluationInputComponents", m_deviceProperties.limits.maxTessellationEvaluationInputComponents);
		a_displayer.attribute("maxTessellationEvaluationOutputComponents", m_deviceProperties.limits.maxTessellationEvaluationOutputComponents);
		a_displayer.attribute("maxGeometryShaderInvocations", m_deviceProperties.limits.maxGeometryShaderInvocations);
		a_displayer.attribute("maxGeometryInputComponents", m_deviceProperties.limits.maxGeometryInputComponents);
		a_displayer.attribute("maxGeometryOutputComponents", m_deviceProperties.limits.maxGeometryOutputComponents);
		a_displayer.attribute("maxGeometryOutputVertices", m_deviceProperties.limits.maxGeometryOutputVertices);
		a_displayer.attribute("maxGeometryTotalOutputComponents", m_deviceProperties.limits.maxGeometryTotalOutputComponents);
		a_displayer.attribute("maxFragmentInputComponents", m_deviceProperties.limits.maxFragmentInputComponents);
		a_displayer.attribute("maxFragmentOutputAttachments", m_deviceProperties.limits.maxFragmentOutputAttachments);
		a_displayer.attribute("maxFragmentDualSrcAttachments", m_deviceProperties.limits.maxFragmentDualSrcAttachments);
		a_displayer.attribute("maxFragmentCombinedOutputResources", m_deviceProperties.limits.maxFragmentCombinedOutputResources);
		a_displayer.attribute("maxComputeSharedMemorySize", m_deviceProperties.limits.maxComputeSharedMemorySize);
		a_displayer.attribute("maxComputeWorkGroupCount[0]", m_deviceProperties.limits.maxComputeWorkGroupCount[0]);
		a_displayer.attribute("maxComputeWorkGroupCount[1]", m_deviceProperties.limits.maxComputeWorkGroupCount[1]);
		a_displayer.attribute("maxComputeWorkGroupCount[2]", m_deviceProperties.limits.maxComputeWorkGroupCount[2]);
		a_displayer.attribute("maxComputeWorkGroupInvocations", m_deviceProperties.limits.maxComputeWorkGroupInvocations);
		a_displayer.attribute("maxComputeWorkGroupSize[0]", m_deviceProperties.limits.maxComputeWorkGroupSize[0]);
		a_displayer.attribute("maxComputeWorkGroupSize[1]", m_deviceProperties.limits.maxComputeWorkGroupSize[1]);
		a_displayer.attribute("maxComputeWorkGroupSize[2]", m_deviceProperties.limits.maxComputeWorkGroupSize[2]);
		a_displayer.attribute("subPixelPrecisionBits", m_deviceProperties.limits.subPixelPrecisionBits);
		a_displayer.attribute("subTexelPrecisionBits", m_deviceProperties.limits.subTexelPrecisionBits);
		a_displayer.attribute("mipmapPrecisionBits", m_deviceProperties.limits.mipmapPrecisionBits);
		a_displayer.attribute("maxDrawIndexedIndexValue", m_deviceProperties.limits.maxDrawIndexedIndexValue);
		a_displayer.attribute("maxDrawIndirectCount", m_deviceProperties.limits.maxDrawIndirectCount);
		a_displayer.attribute("maxSamplerLodBias", m_deviceProperties.limits.maxSamplerLodBias);
		a_displayer.attribute("maxSamplerAnisotropy", m_deviceProperties.limits.maxSamplerAnisotropy);
		a_displayer.attribute("maxViewports", m_deviceProperties.limits.maxViewports);
		a_displayer.attribute("maxViewportDimensions[0]", m_deviceProperties.limits.maxViewportDimensions[0]);
		a_displayer.attribute("maxViewportDimensions[1]", m_deviceProperties.limits.maxViewportDimensions[1]);
		a_displayer.attribute("viewportBoundsRange[0]", m_deviceProperties.limits.viewportBoundsRange[0]);
		a_displayer.attribute("viewportBoundsRange[1]", m_deviceProperties.limits.viewportBoundsRange[1]);
		a_displayer.attribute("viewportSubPixelBits", m_deviceProperties.limits.viewportSubPixelBits);
		a_displayer.attribute("minMemoryMapAlignment", m_deviceProperties.limits.minMemoryMapAlignment);
		a_displayer.attribute("minTexelBufferOffsetAlignment", static_cast<size_t>(m_deviceProperties.limits.minTexelBufferOffsetAlignment));
		a_displayer.attribute("minUniformBufferOffsetAlignment", static_cast<size_t>(m_deviceProperties.limits.minUniformBufferOffsetAlignment));
		a_displayer.attribute("minStorageBufferOffsetAlignment", static_cast<size_t>(m_deviceProperties.limits.minStorageBufferOffsetAlignment));
		a_displayer.attribute("minTexelOffset", m_deviceProperties.limits.minTexelOffset);
		a_displayer.attribute("maxTexelOffset", m_deviceProperties.limits.maxTexelOffset);
		a_displayer.attribute("minTexelGatherOffset", m_deviceProperties.limits.minTexelGatherOffset);
		a_displayer.attribute("maxTexelGatherOffset", m_deviceProperties.limits.maxTexelGatherOffset);
		a_displayer.attribute("minInterpolationOffset", m_deviceProperties.limits.minInterpolationOffset);
		a_displayer.attribute("maxInterpolationOffset", m_deviceProperties.limits.maxInterpolationOffset);
		a_displayer.attribute("subPixelInterpolationOffsetBits", m_deviceProperties.limits.subPixelInterpolationOffsetBits);
		a_displayer.attribute("maxFramebufferWidth", m_deviceProperties.limits.maxFramebufferWidth);
		a_displayer.attribute("maxFramebufferHeight", m_deviceProperties.limits.maxFramebufferHeight);
		a_displayer.attribute("maxFramebufferLayers", m_deviceProperties.limits.maxFramebufferLayers);
		a_displayer.attribute("framebufferColorSampleCounts", Flag<VkSampleCountFlagBits>::to_string(m_deviceProperties.limits.framebufferColorSampleCounts));
		a_displayer.attribute("framebufferDepthSampleCounts", Flag<VkSampleCountFlagBits>::to_string(m_deviceProperties.limits.framebufferDepthSampleCounts));
		a_displayer.attribute("framebufferStencilSampleCounts", Flag<VkSampleCountFlagBits>::to_string(m_deviceProperties.limits.framebufferStencilSampleCounts));
		a_displayer.attribute("framebufferNoAttachmentsSampleCounts", Flag<VkSampleCountFlagBits>::to_string(m_deviceProperties.limits.framebufferNoAttachmentsSampleCounts));
		a_displayer.attribute("maxColorAttachments", m_deviceProperties.limits.maxColorAttachments);
		a_displayer.attribute("sampledImageColorSampleCounts", Flag<VkSampleCountFlagBits>::to_string(m_deviceProperties.limits.sampledImageColorSampleCounts));
		a_displayer.attribute("sampledImageIntegerSampleCounts", Flag<VkSampleCountFlagBits>::to_string(m_deviceProperties.limits.sampledImageIntegerSampleCounts));
		a_displayer.attribute("sampledImageDepthSampleCounts", Flag<VkSampleCountFlagBits>::to_string(m_deviceProperties.limits.sampledImageDepthSampleCounts));
		a_displayer.attribute("sampledImageStencilSampleCounts", Flag<VkSampleCountFlagBits>::to_string(m_deviceProperties.limits.sampledImageStencilSampleCounts));
		a_displayer.attribute("storageImageSampleCounts", Flag<VkSampleCountFlagBits>::to_string(m_deviceProperties.limits.storageImageSampleCounts));
		a_displayer.attribute("maxSampleMaskWords", m_deviceProperties.limits.maxSampleMaskWords);
		a_displayer.attribute("timestampComputeAndGraphics", m_deviceProperties.limits.timestampComputeAndGraphics);
		a_displayer.attribute("timestampPeriod", m_deviceProperties.limits.timestampPeriod);
		a_displayer.attribute("maxClipDistances", m_deviceProperties.limits.maxClipDistances);
		a_displayer.attribute("maxCullDistances", m_deviceProperties.limits.maxCullDistances);
		a_displayer.attribute("maxCombinedClipAndCullDistances", m_deviceProperties.limits.maxCombinedClipAndCullDistances);
		a_displayer.attribute("discreteQueuePriorities", m_deviceProperties.limits.discreteQueuePriorities);
		a_displayer.attribute("pointSizeRange[0]", m_deviceProperties.limits.pointSizeRange[0]);
		a_displayer.attribute("pointSizeRange[1]", m_deviceProperties.limits.pointSizeRange[1]);
		a_displayer.attribute("lineWidthRange[0]", m_deviceProperties.limits.lineWidthRange[0]);
		a_displayer.attribute("lineWidthRange[1]", m_deviceProperties.limits.lineWidthRange[1]);
		a_displayer.attribute("pointSizeGranularity", m_deviceProperties.limits.pointSizeGranularity);
		a_displayer.attribute("lineWidthGranularity", m_deviceProperties.limits.lineWidthGranularity);
		a_displayer.attribute("strictLines", m_deviceProperties.limits.strictLines);
		a_displayer.attribute("standardSampleLocations", m_deviceProperties.limits.standardSampleLocations);
		a_displayer.attribute("optimalBufferCopyOffsetAlignment", static_cast<size_t>(m_deviceProperties.limits.optimalBufferCopyOffsetAlignment));
		a_displayer.attribute("optimalBufferCopyRowPitchAlignment", static_cast<size_t>(m_deviceProperties.limits.optimalBufferCopyRowPitchAlignment));
		a_displayer.attribute("nonCoherentAtomSize", static_cast<size_t>(m_deviceProperties.limits.nonCoherentAtomSize));
		a_displayer.endNode();
	}

	void VK_DeviceCapabilities::displayDeviceSparseProps(IDataDisplayer& a_displayer)const
	{
		a_displayer.beginNode("Device Sparse properties");
		a_displayer.attribute("residencyStandard2DBlockShape", m_deviceProperties.sparseProperties.residencyStandard2DBlockShape);
		a_displayer.attribute("residencyStandard2DMultisampleBlockShape", m_deviceProperties.sparseProperties.residencyStandard2DMultisampleBlockShape);
		a_displayer.attribute("residencyStandard3DBlockShape", m_deviceProperties.sparseProperties.residencyStandard3DBlockShape);
		a_displayer.attribute("residencyAlignedMipSize", m_deviceProperties.sparseProperties.residencyAlignedMipSize);
		a_displayer.attribute("residencyNonResidentStrict", m_deviceProperties.sparseProperties.residencyNonResidentStrict);
		a_displayer.endNode();
	}
	//-----------------------------------------------------------------------------------------------------------------
	void VK_DeviceCapabilities::displayDeviceproperties(IDataDisplayer& a_displayer)const
	{
		a_displayer.attribute("deviceName", m_deviceProperties.deviceName);
		a_displayer.attribute("deviceType", to_string(m_deviceProperties.deviceType));
		a_displayer.attribute("apiVersion", static_cast<unsigned int>(m_deviceProperties.apiVersion));
		a_displayer.attribute("driverVersion", static_cast<unsigned int>(m_deviceProperties.driverVersion));
		a_displayer.attribute("vendorID", static_cast<unsigned int>(m_deviceProperties.vendorID));
		a_displayer.attribute("deviceID", static_cast<unsigned int>(m_deviceProperties.deviceID));

		displayDeviceLimits(a_displayer);
		displayDeviceSparseProps(a_displayer);
	}

	void VK_DeviceCapabilities::displayDeviceQueuesproperties(IDataDisplayer& a_displayer)const
	{
		a_displayer.beginNode("Device Queues");
		for (const auto& familyProp : m_queueFamilies)
		{
			a_displayer.beginNode("Queue");
			a_displayer.attribute("count", familyProp.queueCount);
			a_displayer.attribute("flag", Flag<VkQueueFlagBits>::to_string(familyProp.queueFlags));
			a_displayer.attribute("image granularity width", familyProp.minImageTransferGranularity.width);
			a_displayer.attribute("image granularity height", familyProp.minImageTransferGranularity.height);
			a_displayer.attribute("image granularity depth", familyProp.minImageTransferGranularity.depth);
			a_displayer.endNode();
		}
		a_displayer.endNode();
	}

	void VK_DeviceCapabilities::displayDeviceMemoryProperties(IDataDisplayer& a_displayer)const
	{
		a_displayer.beginNode("Device Memory");

		a_displayer.beginNode("Memory Types");
		for (uint32_t i = 0; i < m_memoryProperties.memoryTypeCount; ++i)
		{
			a_displayer.beginNode("Type");
			a_displayer.attribute("property flags", Flag<VkMemoryPropertyFlagBits>::to_string(m_memoryProperties.memoryTypes[i].propertyFlags));
			a_displayer.attribute("index", m_memoryProperties.memoryTypes[i].heapIndex);
			a_displayer.endNode();
		}
		a_displayer.endNode();

		a_displayer.beginNode("Memory heaps");
		for (uint32_t i = 0; i < m_memoryProperties.memoryHeapCount; ++i)
		{
			a_displayer.beginNode("Heap");
			a_displayer.attribute("flags", Flag<VkMemoryHeapFlagBits>::to_string(m_memoryProperties.memoryHeaps[i].flags));
			a_displayer.attribute("size", m_memoryProperties.memoryHeaps[i].size);
			a_displayer.endNode();
		}
		a_displayer.endNode();

		a_displayer.endNode();
	}

	void VK_DeviceCapabilities::displayDeviceFeatures(IDataDisplayer& a_displayer)const
	{
		a_displayer.beginNode("Device Features");

		a_displayer.attribute("robustBufferAccess", static_cast<bool>(m_deviceFeatures.robustBufferAccess));
		a_displayer.attribute("fullDrawIndexUint32", static_cast<bool>(m_deviceFeatures.fullDrawIndexUint32));
		a_displayer.attribute("imageCubeArray", static_cast<bool>(m_deviceFeatures.imageCubeArray));
		a_displayer.attribute("independentBlend", static_cast<bool>(m_deviceFeatures.independentBlend));
		a_displayer.attribute("geometryShader", static_cast<bool>(m_deviceFeatures.geometryShader));
		a_displayer.attribute("tessellationShader", static_cast<bool>(m_deviceFeatures.tessellationShader));
		a_displayer.attribute("sampleRateShading", static_cast<bool>(m_deviceFeatures.sampleRateShading));
		a_displayer.attribute("dualSrcBlend", static_cast<bool>(m_deviceFeatures.dualSrcBlend));
		a_displayer.attribute("logicOp", static_cast<bool>(m_deviceFeatures.logicOp));
		a_displayer.attribute("multiDrawIndirect", static_cast<bool>(m_deviceFeatures.multiDrawIndirect));
		a_displayer.attribute("drawIndirectFirstInstance", static_cast<bool>(m_deviceFeatures.drawIndirectFirstInstance));
		a_displayer.attribute("depthClamp", static_cast<bool>(m_deviceFeatures.depthClamp));
		a_displayer.attribute("depthBiasClamp", static_cast<bool>(m_deviceFeatures.depthBiasClamp));
		a_displayer.attribute("fillModeNonSolid", static_cast<bool>(m_deviceFeatures.fillModeNonSolid));
		a_displayer.attribute("depthBounds", static_cast<bool>(m_deviceFeatures.depthBounds));
		a_displayer.attribute("wideLines", static_cast<bool>(m_deviceFeatures.wideLines));
		a_displayer.attribute("largePoints", static_cast<bool>(m_deviceFeatures.largePoints));
		a_displayer.attribute("alphaToOne", static_cast<bool>(m_deviceFeatures.alphaToOne));
		a_displayer.attribute("multiViewport", static_cast<bool>(m_deviceFeatures.multiViewport));
		a_displayer.attribute("samplerAnisotropy", static_cast<bool>(m_deviceFeatures.samplerAnisotropy));
		a_displayer.attribute("textureCompressionETC2", static_cast<bool>(m_deviceFeatures.textureCompressionETC2));
		a_displayer.attribute("textureCompressionASTC_LDR", static_cast<bool>(m_deviceFeatures.textureCompressionASTC_LDR));
		a_displayer.attribute("textureCompressionBC", static_cast<bool>(m_deviceFeatures.textureCompressionBC));
		a_displayer.attribute("occlusionQueryPrecise", static_cast<bool>(m_deviceFeatures.occlusionQueryPrecise));
		a_displayer.attribute("pipelineStatisticsQuery", static_cast<bool>(m_deviceFeatures.pipelineStatisticsQuery));
		a_displayer.attribute("vertexPipelineStoresAndAtomics", static_cast<bool>(m_deviceFeatures.vertexPipelineStoresAndAtomics));
		a_displayer.attribute("fragmentStoresAndAtomics", static_cast<bool>(m_deviceFeatures.fragmentStoresAndAtomics));
		a_displayer.attribute("shaderTessellationAndGeometryPointSize", static_cast<bool>(m_deviceFeatures.shaderTessellationAndGeometryPointSize));
		a_displayer.attribute("shaderImageGatherExtended", static_cast<bool>(m_deviceFeatures.shaderImageGatherExtended));
		a_displayer.attribute("shaderStorageImageExtendedFormats", static_cast<bool>(m_deviceFeatures.shaderStorageImageExtendedFormats));
		a_displayer.attribute("shaderStorageImageMultisample", static_cast<bool>(m_deviceFeatures.shaderStorageImageMultisample));
		a_displayer.attribute("shaderStorageImageReadWithoutFormat", static_cast<bool>(m_deviceFeatures.shaderStorageImageReadWithoutFormat));
		a_displayer.attribute("shaderStorageImageWriteWithoutFormat", static_cast<bool>(m_deviceFeatures.shaderStorageImageWriteWithoutFormat));
		a_displayer.attribute("shaderUniformBufferArrayDynamicIndexing", static_cast<bool>(m_deviceFeatures.shaderUniformBufferArrayDynamicIndexing));
		a_displayer.attribute("shaderSampledImageArrayDynamicIndexing", static_cast<bool>(m_deviceFeatures.shaderSampledImageArrayDynamicIndexing));
		a_displayer.attribute("shaderStorageBufferArrayDynamicIndexing", static_cast<bool>(m_deviceFeatures.shaderStorageBufferArrayDynamicIndexing));
		a_displayer.attribute("shaderStorageImageArrayDynamicIndexing", static_cast<bool>(m_deviceFeatures.shaderStorageImageArrayDynamicIndexing));
		a_displayer.attribute("shaderClipDistance", static_cast<bool>(m_deviceFeatures.shaderClipDistance));
		a_displayer.attribute("shaderCullDistance", static_cast<bool>(m_deviceFeatures.shaderCullDistance));
		a_displayer.attribute("shaderFloat64", static_cast<bool>(m_deviceFeatures.shaderFloat64));
		a_displayer.attribute("shaderInt64", static_cast<bool>(m_deviceFeatures.shaderInt64));
		a_displayer.attribute("shaderInt16", static_cast<bool>(m_deviceFeatures.shaderInt16));
		a_displayer.attribute("shaderResourceResidency", static_cast<bool>(m_deviceFeatures.shaderResourceResidency));
		a_displayer.attribute("shaderResourceMinLod", static_cast<bool>(m_deviceFeatures.shaderResourceMinLod));
		a_displayer.attribute("sparseBinding", static_cast<bool>(m_deviceFeatures.sparseBinding));
		a_displayer.attribute("sparseResidencyBuffer", static_cast<bool>(m_deviceFeatures.sparseResidencyBuffer));
		a_displayer.attribute("sparseResidencyImage2D", static_cast<bool>(m_deviceFeatures.sparseResidencyImage2D));
		a_displayer.attribute("sparseResidencyImage3D", static_cast<bool>(m_deviceFeatures.sparseResidencyImage3D));
		a_displayer.attribute("sparseResidency2Samples", static_cast<bool>(m_deviceFeatures.sparseResidency2Samples));
		a_displayer.attribute("sparseResidency4Samples", static_cast<bool>(m_deviceFeatures.sparseResidency4Samples));
		a_displayer.attribute("sparseResidency8Samples", static_cast<bool>(m_deviceFeatures.sparseResidency8Samples));
		a_displayer.attribute("sparseResidency16Samples", static_cast<bool>(m_deviceFeatures.sparseResidency16Samples));
		a_displayer.attribute("sparseResidencyAliased", static_cast<bool>(m_deviceFeatures.sparseResidencyAliased));
		a_displayer.attribute("variableMultisampleRate", static_cast<bool>(m_deviceFeatures.variableMultisampleRate));
		a_displayer.attribute("inheritedQueries", static_cast<bool>(m_deviceFeatures.inheritedQueries));

		a_displayer.endNode();
	}

	void VK_DeviceCapabilities::displayDeviceFormats(IDataDisplayer& a_displayer)const
	{
		a_displayer.beginNode("Device Formats properties");
		for (const auto& format : m_formatsProperties)
		{
			a_displayer.beginNode("Formats");
			a_displayer.attribute("format", to_string(format.format));
			a_displayer.beginNode("Properties");
			a_displayer.attribute("Buffer features", Flag<VkFormatFeatureFlagBits>::to_string(format.properties.bufferFeatures));
			a_displayer.attribute("Linear tiling features", Flag<VkFormatFeatureFlagBits>::to_string(format.properties.linearTilingFeatures));
			a_displayer.attribute("Optimal tiling features", Flag<VkFormatFeatureFlagBits>::to_string(format.properties.optimalTilingFeatures));
			a_displayer.endNode();
			a_displayer.endNode();
		}
		a_displayer.endNode();
	}

	void VK_DeviceCapabilities::displaySwapchain(IDataDisplayer& a_displayer)const
	{
		a_displayer.beginNode("Swapchain capabilities");

		a_displayer.beginNode("Surface capabilities");
		a_displayer.attribute("minImageCount", m_swapChainCapabilities.surfaceCapabilities.minImageCount);
		a_displayer.attribute("maxImageCount", m_swapChainCapabilities.surfaceCapabilities.maxImageCount);
		a_displayer.attribute("currentExtent.width", m_swapChainCapabilities.surfaceCapabilities.currentExtent.width);
		a_displayer.attribute("currentExtent.height", m_swapChainCapabilities.surfaceCapabilities.currentExtent.height);
		a_displayer.attribute("minImageExtent.width", m_swapChainCapabilities.surfaceCapabilities.minImageExtent.width);
		a_displayer.attribute("minImageExtent.height", m_swapChainCapabilities.surfaceCapabilities.minImageExtent.height);
		a_displayer.attribute("maxImageExtent.width", m_swapChainCapabilities.surfaceCapabilities.maxImageExtent.width);
		a_displayer.attribute("maxImageExtent.height", m_swapChainCapabilities.surfaceCapabilities.maxImageExtent.height);
		a_displayer.attribute("maxImageArrayLayers", m_swapChainCapabilities.surfaceCapabilities.maxImageArrayLayers);
		a_displayer.attribute("supportedTransforms", Flag<VkSurfaceTransformFlagBitsKHR>::to_string(m_swapChainCapabilities.surfaceCapabilities.supportedTransforms));
		a_displayer.attribute("currentTransform", to_string(m_swapChainCapabilities.surfaceCapabilities.currentTransform));
		a_displayer.attribute("supportedCompositeAlpha", Flag< VkCompositeAlphaFlagBitsKHR>::to_string(m_swapChainCapabilities.surfaceCapabilities.supportedCompositeAlpha));
		a_displayer.attribute("supportedUsageFlags", Flag<VkImageUsageFlagBits>::to_string(m_swapChainCapabilities.surfaceCapabilities.supportedUsageFlags));
		a_displayer.endNode();

		a_displayer.beginNode("Supported formats");
		for (const auto& format : m_swapChainCapabilities.supportedFormats)
		{
			a_displayer.beginNode("Format");
			a_displayer.attribute("format", to_string(format.format));
			a_displayer.attribute("color space", to_string(format.colorSpace));
			a_displayer.endNode();
		}
		a_displayer.endNode();

		a_displayer.beginNode("Supported modes");
		for (const auto mode : m_swapChainCapabilities.supportedModes)
		{
			a_displayer.attribute("mode", to_string(mode));
		}
		a_displayer.endNode();

		a_displayer.endNode();
	}

	VK_DeviceCapabilities::VK_DeviceCapabilities(const VkPhysicalDevice a_device) : m_physicalDevice{ a_device }
	{
		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, &queueFamilyCount, nullptr);
		m_queueFamilies.resize(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, &queueFamilyCount, m_queueFamilies.data());
		//------------------------------------------------------------------------------------------------------
		uint32_t extensionCount = 0;
		vkEnumerateDeviceExtensionProperties(m_physicalDevice, nullptr, &extensionCount, nullptr);
		m_extensions.resize(extensionCount);
		vkEnumerateDeviceExtensionProperties(m_physicalDevice, nullptr, &extensionCount, m_extensions.data());
		//------------------------------------------------------------------------------------------------------
		vkGetPhysicalDeviceProperties(m_physicalDevice, &m_deviceProperties);
		vkGetPhysicalDeviceFeatures(m_physicalDevice, &m_deviceFeatures);
		vkGetPhysicalDeviceMemoryProperties(m_physicalDevice, &m_memoryProperties);
		//------------------------------------------------------------------------------------------------------
		getFormatsProperties();
	}

	void VK_DeviceCapabilities::display(IDataDisplayer& a_displayer)const
	{
		displayDeviceproperties(a_displayer);
		displayDeviceQueuesproperties(a_displayer);
		displayDeviceMemoryProperties(a_displayer);
		displayDeviceFeatures(a_displayer);
		displayDeviceFormats(a_displayer);
		displaySwapchain(a_displayer);
		displayDeviceLimits(a_displayer);
		displayDeviceSparseProps(a_displayer);
	}

	void VK_DeviceCapabilities::supportedFormat(std::vector<VkFormat>& a_formats, const VkImageTiling a_tiling, const VkFormatFeatureFlags a_featureFlag)const
	{
		std::for_each(m_formatsProperties.cbegin(), m_formatsProperties.cend(), [&](const auto& a_prop)
			{
				// Depending on tiling choice, need to check for different bit flag
				switch (a_tiling)
				{
				case VK_IMAGE_TILING_LINEAR:
					if ((a_prop.properties.linearTilingFeatures & a_featureFlag) == a_featureFlag)
						a_formats.push_back(a_prop.format);
					break;

				case VK_IMAGE_TILING_OPTIMAL:
					if ((a_prop.properties.optimalTilingFeatures & a_featureFlag) == a_featureFlag)
						a_formats.push_back(a_prop.format);
					break;

				default:
					break;
				}
			});
	}

	uint32_t VK_DeviceCapabilities::memoryTypeIndex(uint32_t a_memTypeBits, VkMemoryPropertyFlags a_flags)const
	{
		for (uint32_t iIndex = 0; iIndex < m_memoryProperties.memoryTypeCount; iIndex++)
		{
			if ((a_memTypeBits & (1 << iIndex))														// Index of memory type must match corresponding bit in allowedTypes
				&& (m_memoryProperties.memoryTypes[iIndex].propertyFlags & a_flags) == a_flags)		// Desired property bit flags are part of memory type's property flags
			{
				// This memory type is valid, so return its index
				return iIndex;
			}
		}
		throw Vulkan::VK_Exception("Can't find Memory index.", std::source_location::current());
	}

	VkPresentModeKHR VK_DeviceCapabilities::bestPresentationMode()const
	{
		if (std::find(m_swapChainCapabilities.supportedModes.cbegin(), m_swapChainCapabilities.supportedModes.cend(), VK_PRESENT_MODE_MAILBOX_KHR) != m_swapChainCapabilities.supportedModes.cend())
			return VK_PRESENT_MODE_MAILBOX_KHR;
		return VK_PRESENT_MODE_FIFO_KHR;
	}

	VkSurfaceFormatKHR VK_DeviceCapabilities::bestSurfaceFormat()const
	{
		// If only 1 format available and is undefined, then this means ALL formats are available (no restrictions)
		if (m_swapChainCapabilities.supportedFormats.size() == 1 && m_swapChainCapabilities.supportedFormats[0].format == VK_FORMAT_UNDEFINED)
			return{ VK_FORMAT_R8G8B8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };

		// If restricted, search for optimal format
		auto iter = std::find_if(m_swapChainCapabilities.supportedFormats.begin(), m_swapChainCapabilities.supportedFormats.end(), [&](const auto& format)
			{
				return (format.format == VK_FORMAT_R8G8B8A8_UNORM || format.format == VK_FORMAT_B8G8R8A8_UNORM)
					&& format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
			});
		if (iter != m_swapChainCapabilities.supportedFormats.end())
			return *iter;

		// If can't find optimal format, then just return first format
		return m_swapChainCapabilities.supportedFormats[0];
	}

	void VK_DeviceCapabilities::queues(const std::shared_ptr<VK_WindowSystemProxy>& a_pWinProxy, DeviceQueuesConfiguration& a_queueConf)const
	{
		for (auto& queueConf : a_queueConf.vQueueConf)
		{
			int iFamilyIndex = 0;
			for (const auto& queueCap : m_queueFamilies)
			{
				if (queueCap.queueCount > 0)
				{
					if (queueConf.type == (queueConf.type & queueCap.queueFlags))
					{
						queueConf.index = iFamilyIndex;
						if (a_pWinProxy)
						{
							VkBool32 presentationSupport = VK_FALSE;
							VK_CHECK(vkGetPhysicalDeviceSurfaceSupportKHR(m_physicalDevice, iFamilyIndex, a_pWinProxy->surface(), &presentationSupport))
								queueConf.presentationSupport = presentationSupport == VK_TRUE;
						}
					}
				}
				++iFamilyIndex;
			}
		}
	}

	void VK_DeviceCapabilities::getSwapChainCapabilities(const VkSurfaceKHR a_surface)
	{
		VK_CHECK(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_physicalDevice, a_surface, &m_swapChainCapabilities.surfaceCapabilities));

		uint32_t formatCount = 0;
		VK_CHECK(vkGetPhysicalDeviceSurfaceFormatsKHR(m_physicalDevice, a_surface, &formatCount, nullptr));
		if (formatCount > 0)
		{
			m_swapChainCapabilities.supportedFormats.resize(static_cast<int>(formatCount));
			VK_CHECK(vkGetPhysicalDeviceSurfaceFormatsKHR(m_physicalDevice, a_surface, &formatCount, m_swapChainCapabilities.supportedFormats.data()));
		}

		uint32_t presentCount = 0;
		VK_CHECK(vkGetPhysicalDeviceSurfacePresentModesKHR(m_physicalDevice, a_surface, &presentCount, nullptr));
		if (presentCount > 0)
		{
			m_swapChainCapabilities.supportedModes.resize(static_cast<int>(presentCount));
			VK_CHECK(vkGetPhysicalDeviceSurfacePresentModesKHR(m_physicalDevice, a_surface, &presentCount, m_swapChainCapabilities.supportedModes.data()));
		}
	}
}