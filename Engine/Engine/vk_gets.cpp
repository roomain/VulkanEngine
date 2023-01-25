#include "pch.h"
#include "vk_ext_struct.h"

namespace Vulkan
{


	void getQueueFamiliesProperties(const VkPhysicalDevice a_device, std::vector<VkQueueFamilyProperties>& a_familiesProperties)
	{
		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(a_device, &queueFamilyCount, nullptr);
		a_familiesProperties.resize(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(a_device, &queueFamilyCount, a_familiesProperties.data());
	}

	void getFormatsProperties(const VkPhysicalDevice a_device, std::vector<FormatProperty>& a_formatsProperties)
	{
		FormatProperty formatProp = { .format = VK_FORMAT_R4G4_UNORM_PACK8 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R4G4B4A4_UNORM_PACK16 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B4G4R4A4_UNORM_PACK16 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R5G6B5_UNORM_PACK16 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B5G6R5_UNORM_PACK16 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R5G5B5A1_UNORM_PACK16 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B5G5R5A1_UNORM_PACK16 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A1R5G5B5_UNORM_PACK16 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8_UNORM };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8_SNORM };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8_USCALED };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8_SSCALED };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8_UINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8_SINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8_SRGB };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8_UNORM };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8_SNORM };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8_USCALED };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8_SSCALED };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8_UINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8_SINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8_SRGB };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8B8_UNORM };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8B8_SNORM };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8B8_USCALED };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8B8_SSCALED };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8B8_UINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8B8_SINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8B8_SRGB };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B8G8R8_UNORM };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B8G8R8_SNORM };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B8G8R8_USCALED };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B8G8R8_SSCALED };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B8G8R8_UINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B8G8R8_SINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B8G8R8_SRGB };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8B8A8_UNORM };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8B8A8_SNORM };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8B8A8_USCALED };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8B8A8_SSCALED };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8B8A8_UINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8B8A8_SINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R8G8B8A8_SRGB };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B8G8R8A8_UNORM };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B8G8R8A8_SNORM };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B8G8R8A8_USCALED };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B8G8R8A8_SSCALED };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B8G8R8A8_UINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B8G8R8A8_SINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B8G8R8A8_SRGB };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A8B8G8R8_UNORM_PACK32 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A8B8G8R8_SNORM_PACK32 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A8B8G8R8_USCALED_PACK32 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A8B8G8R8_SSCALED_PACK32 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A8B8G8R8_UINT_PACK32 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A8B8G8R8_SINT_PACK32 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A8B8G8R8_SRGB_PACK32 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A2R10G10B10_UNORM_PACK32 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A2R10G10B10_SNORM_PACK32 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A2R10G10B10_USCALED_PACK32 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A2R10G10B10_SSCALED_PACK32 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A2R10G10B10_UINT_PACK32 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A2R10G10B10_SINT_PACK32 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A2B10G10R10_UNORM_PACK32 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A2B10G10R10_SNORM_PACK32 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A2B10G10R10_USCALED_PACK32 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A2B10G10R10_SSCALED_PACK32 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A2B10G10R10_UINT_PACK32 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A2B10G10R10_SINT_PACK32 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16_UNORM };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16_SNORM };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16_USCALED };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16_SSCALED };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16_UINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16_SINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16_SFLOAT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16_UNORM };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16_SNORM };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16_USCALED };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16_SSCALED };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16_UINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16_SINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16_SFLOAT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16B16_UNORM };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16B16_SNORM };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16B16_USCALED };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16B16_SSCALED };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16B16_UINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16B16_SINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16B16_SFLOAT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16B16A16_UNORM };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16B16A16_SNORM };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16B16A16_USCALED };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16B16A16_SSCALED };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16B16A16_UINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16B16A16_SINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R16G16B16A16_SFLOAT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R32_UINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R32_SINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R32_SFLOAT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R32G32_UINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R32G32_SINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R32G32_SFLOAT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R32G32B32_UINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R32G32B32_SINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R32G32B32_SFLOAT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R32G32B32A32_UINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R32G32B32A32_SINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R32G32B32A32_SFLOAT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R64_UINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R64_SINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R64_SFLOAT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R64G64_UINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R64G64_SINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R64G64_SFLOAT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R64G64B64_UINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R64G64B64_SINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R64G64B64_SFLOAT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R64G64B64A64_UINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R64G64B64A64_SINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R64G64B64A64_SFLOAT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B10G11R11_UFLOAT_PACK32 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_E5B9G9R9_UFLOAT_PACK32 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_D16_UNORM };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_X8_D24_UNORM_PACK32 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_D32_SFLOAT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_S8_UINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_D16_UNORM_S8_UINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_D24_UNORM_S8_UINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_D32_SFLOAT_S8_UINT };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_BC1_RGB_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_BC1_RGB_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_BC1_RGBA_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_BC1_RGBA_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_BC2_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_BC2_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_BC3_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_BC3_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_BC4_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_BC4_SNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_BC5_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_BC5_SNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_BC6H_UFLOAT_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_BC6H_SFLOAT_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_BC7_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_BC7_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_EAC_R11_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_EAC_R11_SNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_EAC_R11G11_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_EAC_R11G11_SNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_4x4_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_4x4_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_5x4_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_5x4_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_5x5_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_5x5_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_6x5_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_6x5_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_6x6_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_6x6_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_8x5_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_8x5_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_8x6_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_8x6_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_8x8_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_8x8_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_10x5_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_10x5_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_10x6_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_10x6_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_10x8_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_10x8_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_10x10_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_10x10_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_12x10_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_12x10_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_12x12_UNORM_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_12x12_SRGB_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G8B8G8R8_422_UNORM };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B8G8R8G8_422_UNORM };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G8_B8R8_2PLANE_420_UNORM };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G8_B8R8_2PLANE_422_UNORM };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R10X6_UNORM_PACK16 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R10X6G10X6_UNORM_2PACK16 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R12X4_UNORM_PACK16 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R12X4G12X4_UNORM_2PACK16 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G16B16G16R16_422_UNORM };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_B16G16R16G16_422_UNORM };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G16_B16R16_2PLANE_420_UNORM };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G16_B16R16_2PLANE_422_UNORM };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G8_B8R8_2PLANE_444_UNORM };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G10X6_B10X6R10X6_2PLANE_444_UNORM_3PACK16 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G12X4_B12X4R12X4_2PLANE_444_UNORM_3PACK16 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_G16_B16R16_2PLANE_444_UNORM };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A4R4G4B4_UNORM_PACK16 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_A4B4G4R4_UNORM_PACK16 };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_4x4_SFLOAT_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_5x4_SFLOAT_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_5x5_SFLOAT_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_6x5_SFLOAT_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_6x6_SFLOAT_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_8x5_SFLOAT_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_8x6_SFLOAT_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_8x8_SFLOAT_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_10x5_SFLOAT_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_10x6_SFLOAT_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_10x8_SFLOAT_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_10x10_SFLOAT_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_12x10_SFLOAT_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_ASTC_12x12_SFLOAT_BLOCK };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_PVRTC1_4BPP_UNORM_BLOCK_IMG };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_PVRTC2_2BPP_UNORM_BLOCK_IMG };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_PVRTC2_4BPP_UNORM_BLOCK_IMG };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_PVRTC1_2BPP_SRGB_BLOCK_IMG };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_PVRTC1_4BPP_SRGB_BLOCK_IMG };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_PVRTC2_2BPP_SRGB_BLOCK_IMG };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

		formatProp = FormatProperty{ .format = VK_FORMAT_PVRTC2_4BPP_SRGB_BLOCK_IMG };
		vkGetPhysicalDeviceFormatProperties(a_device, formatProp.format, &formatProp.properties);
		a_formatsProperties.push_back(formatProp);

	}

	void getDeviceExtensions(const VkPhysicalDevice a_device, std::vector<VkExtensionProperties>& a_extensions)
	{
		uint32_t extensionCount = 0;
		vkEnumerateDeviceExtensionProperties(a_device, nullptr, &extensionCount, nullptr);
		a_extensions.resize(extensionCount);
		vkEnumerateDeviceExtensionProperties(a_device, nullptr, &extensionCount, a_extensions.data());
	}

	void getSwapChainCapabilities(const VkPhysicalDevice a_device, const VkSurfaceKHR a_surface, SwapchainCapabilities& a_swapChainCap)
	{
		VK_CHECK(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(a_device, a_surface, &a_swapChainCap.surfaceCapabilities));

		uint32_t formatCount = 0;
		VK_CHECK(vkGetPhysicalDeviceSurfaceFormatsKHR(a_device, a_surface, &formatCount, nullptr));
		if (formatCount > 0)
		{
			a_swapChainCap.supportedFormats.resize(static_cast<int>(formatCount));
			VK_CHECK(vkGetPhysicalDeviceSurfaceFormatsKHR(a_device, a_surface, &formatCount, a_swapChainCap.supportedFormats.data()));
		}

		uint32_t presentCount = 0;
		VK_CHECK(vkGetPhysicalDeviceSurfacePresentModesKHR(a_device, a_surface, &presentCount, nullptr));
		if (presentCount > 0)
		{
			a_swapChainCap.supportedModes.resize(static_cast<int>(presentCount));
			VK_CHECK(vkGetPhysicalDeviceSurfacePresentModesKHR(a_device, a_surface, &presentCount, a_swapChainCap.supportedModes.data()));
		}
	}

	void getDeviceCapabilities(const VkPhysicalDevice a_device, DeviceCapabilities& a_capabilities)
	{
		vkGetPhysicalDeviceProperties(a_device, &a_capabilities.deviceProperties);
		vkGetPhysicalDeviceFeatures(a_device, &a_capabilities.deviceFeatures);
		vkGetPhysicalDeviceMemoryProperties(a_device, &a_capabilities.memoryProperties);
		getFormatsProperties(a_device, a_capabilities.formatsProperties);
		getQueueFamiliesProperties(a_device, a_capabilities.queueFamilies);
		getDeviceExtensions(a_device, a_capabilities.extensions);
	}

	void getDeviceQueues(const VkPhysicalDevice a_physicalDevice, const VkSurfaceKHR a_surface, DeviceQueuesConfiguration& a_queueConf)
	{
		a_queueConf.reset();
		// get memory properties
		std::vector<VkQueueFamilyProperties> queuesProperties;
		getQueueFamiliesProperties(a_physicalDevice, queuesProperties);

		// check an fill queues
		int iFamilyIndex = 0;

		VkBool32 presentationSupport = false;
		for (const auto& queueFamily : queuesProperties)
		{
			if (queueFamily.queueCount > 0)// at least on queue
			{
				for (auto& queueConf : a_queueConf.vQueueConf)
				{
					if (queueConf.type == (queueConf.type & queueFamily.queueFlags))
					{
						queueConf.index = iFamilyIndex;
						vkGetPhysicalDeviceSurfaceSupportKHR(a_physicalDevice, iFamilyIndex, a_surface, &presentationSupport);
						queueConf.presentationSupport = presentationSupport == VK_TRUE;
						break;
					}
				}
			}
			++iFamilyIndex;
		}
	}

	//---------------------------------------------------------------------------------------------------------------------------------------------------------

	VkFormat getSupportedFormat(const VkPhysicalDevice a_device, const std::vector<VkFormat>& a_formats, const VkImageTiling a_tiling, const VkFormatFeatureFlags a_featureFlag)
	{
		// Loop through options and find compatible one
		for (VkFormat format : a_formats)
		{
			// Get properties for give format on this device
			VkFormatProperties properties;
			vkGetPhysicalDeviceFormatProperties(a_device, format, &properties);

			// Depending on tiling choice, need to check for different bit flag
			switch (a_tiling)
			{
			case VK_IMAGE_TILING_LINEAR:
				if ((properties.linearTilingFeatures & a_featureFlag) == a_featureFlag)
					return format;
				break;

			case VK_IMAGE_TILING_OPTIMAL:
				if ((properties.optimalTilingFeatures & a_featureFlag) == a_featureFlag)
					return format;
				break;

			default:
				break;
			}
		}

		throw VK_Exception("Failed to find a matching format!", std::source_location::current());
	}

	VkFormat getSupportedFormat(const VkPhysicalDevice a_device, std::vector<VkFormat>&& a_formats, VkImageTiling&& a_tiling, VkFormatFeatureFlags&& a_featureFlag)
	{
		// Loop through options and find compatible one
		for (VkFormat format : a_formats)
		{
			// Get properties for give format on this device
			VkFormatProperties properties;
			vkGetPhysicalDeviceFormatProperties(a_device, format, &properties);

			// Depending on tiling choice, need to check for different bit flag
			switch (a_tiling)
			{
			case VK_IMAGE_TILING_LINEAR:
				if ((properties.linearTilingFeatures & a_featureFlag) == a_featureFlag)
					return format;
				break;

			case VK_IMAGE_TILING_OPTIMAL:
				if ((properties.optimalTilingFeatures & a_featureFlag) == a_featureFlag)
					return format;
				break;

			default:
				break;
			}
		}
		throw VK_Exception("Failed to find a matching format!", std::source_location::current());
	}

	uint32_t getMemoryTypeIndex(const VkPhysicalDeviceMemoryProperties& a_memProperties, uint32_t a_memTypeBits, VkMemoryPropertyFlags a_flags)
	{
		for (uint32_t iIndex = 0; iIndex < a_memProperties.memoryTypeCount; iIndex++)
		{
			if ((a_memTypeBits & (1 << iIndex))														// Index of memory type must match corresponding bit in allowedTypes
				&& (a_memProperties.memoryTypes[iIndex].propertyFlags & a_flags) == a_flags)		// Desired property bit flags are part of memory type's property flags
			{
				// This memory type is valid, so return its index
				return iIndex;
			}
		}
		throw Vulkan::VK_Exception("Can't find Memory index.", std::source_location::current());
	}


	VkPresentModeKHR getBestPresentationMode(const std::vector<VkPresentModeKHR>& a_vPresentationModes)
	{
		if (std::find(a_vPresentationModes.cbegin(), a_vPresentationModes.cend(), VK_PRESENT_MODE_MAILBOX_KHR) != a_vPresentationModes.cend())
			return VK_PRESENT_MODE_MAILBOX_KHR;

		return VK_PRESENT_MODE_FIFO_KHR;
	}
}