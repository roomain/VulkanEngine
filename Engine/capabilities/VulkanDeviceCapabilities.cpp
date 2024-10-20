#include "pch.h"
#include "common/enumerate.h"
#include "VulkanDeviceCapabilities.h"
#include "vulkan_enum_to_string.h"
#include "Vulkan_macros.h"
#include "LoggingSystem/Exception.h"


VulkanDeviceCapabilities::VulkanDeviceCapabilities(const uint32_t a_deviceIndex, const VkPhysicalDevice a_device) :
    m_deviceIndex{ a_deviceIndex }, m_physicalDevice { a_device }
{
    enumerate(&vkEnumerateDeviceExtensionProperties, m_extensions, m_physicalDevice, nullptr);
    enumerate(&vkEnumerateDeviceLayerProperties, m_layersProperties, m_physicalDevice);
    enumerate(&vkGetPhysicalDeviceQueueFamilyProperties, m_queueFamilies, m_physicalDevice);
    //------------------------------------------------------------------------------------------------------
    vkGetPhysicalDeviceProperties(m_physicalDevice, &m_deviceProperties);
    vkGetPhysicalDeviceFeatures(m_physicalDevice, &m_deviceFeatures);
    vkGetPhysicalDeviceMemoryProperties(m_physicalDevice, &m_memoryProperties);
    

    for (int format = VK_FORMAT_R4G4_UNORM_PACK8; format <= VK_FORMAT_ASTC_12x12_SRGB_BLOCK; ++format)
    {
        VkFormatProperties prop;
        vkGetPhysicalDeviceFormatProperties(m_physicalDevice, static_cast<VkFormat>(format), &prop);
        m_formatsCapabilities.emplace(static_cast<VkFormat>(format), prop);
    }

    for (int format = VK_FORMAT_G8B8G8R8_422_UNORM; format <= VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM; ++format)
    {
        VkFormatProperties prop;
        vkGetPhysicalDeviceFormatProperties(m_physicalDevice, static_cast<VkFormat>(format), &prop);
        m_formatsCapabilities.emplace(static_cast<VkFormat>(format), prop);
    }

    for (int format = VK_FORMAT_G8_B8R8_2PLANE_444_UNORM; format <= VK_FORMAT_G16_B16R16_2PLANE_444_UNORM; ++format)
    {
        VkFormatProperties prop;
        vkGetPhysicalDeviceFormatProperties(m_physicalDevice, static_cast<VkFormat>(format), &prop);
        m_formatsCapabilities.emplace(static_cast<VkFormat>(format), prop);
    }

    for (int format = VK_FORMAT_A4R4G4B4_UNORM_PACK16; format <= VK_FORMAT_A4B4G4R4_UNORM_PACK16; ++format)
    {
        VkFormatProperties prop;
        vkGetPhysicalDeviceFormatProperties(m_physicalDevice, static_cast<VkFormat>(format), &prop);
        m_formatsCapabilities.emplace(static_cast<VkFormat>(format), prop);
    }

    for (int format = VK_FORMAT_ASTC_4x4_SFLOAT_BLOCK; format <= VK_FORMAT_ASTC_12x12_SFLOAT_BLOCK; ++format)
    {
        VkFormatProperties prop;
        vkGetPhysicalDeviceFormatProperties(m_physicalDevice, static_cast<VkFormat>(format), &prop);
        m_formatsCapabilities.emplace(static_cast<VkFormat>(format), prop);
    }

    for (int format = VK_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG; format <= VK_FORMAT_PVRTC2_4BPP_SRGB_BLOCK_IMG; ++format)
    {
        VkFormatProperties prop;
        vkGetPhysicalDeviceFormatProperties(m_physicalDevice, static_cast<VkFormat>(format), &prop);
        m_formatsCapabilities.emplace(static_cast<VkFormat>(format), prop);
    }
}

VkPhysicalDevice VulkanDeviceCapabilities::physicalDevice()const
{
    return m_physicalDevice;
}

VulkanDeviceInfo VulkanDeviceCapabilities::deviceInfo()const
{
    return VulkanDeviceInfo{
        .deviceIndex = m_deviceIndex,
        .name = std::string{m_deviceProperties.deviceName},
        .deviceType = to_string(m_deviceProperties.deviceType),
        .apiVersion = m_deviceProperties.apiVersion,
        .driverVersion = m_deviceProperties.driverVersion
    };
}

void VulkanDeviceCapabilities::supportedFormats(std::vector<VkFormat>& a_vFormat)const
{
    for(const auto&[key, value] : m_formatsCapabilities)
        a_vFormat.emplace_back(key);
}

const VkFormatProperties VulkanDeviceCapabilities::formatProperties(const VkFormat a_format)const
{
    if(const auto iter = m_formatsCapabilities.find(a_format); iter != m_formatsCapabilities.cend())
        return iter->second;
    throw Exception("Unsupported format");
}

const std::optional<VulkanSwapchainCapabilities> VulkanDeviceCapabilities::swapchainCapabilties()const
{
    return m_swapChainCapabilities;
}

VulkanDeviceCapabilities::Queue_const_iterator VulkanDeviceCapabilities::queueBegin()const noexcept
{
    return m_queueFamilies.cbegin();
}

VulkanDeviceCapabilities::Queue_const_iterator VulkanDeviceCapabilities::queueEnd()const noexcept
{
    return m_queueFamilies.cend();
}

VulkanDeviceCapabilities::Extension_const_iterator VulkanDeviceCapabilities::extensionBegin()const noexcept
{
    return m_extensions.cbegin();
}

VulkanDeviceCapabilities::Extension_const_iterator VulkanDeviceCapabilities::extensionEnd()const noexcept
{
    return m_extensions.cend();
}

VulkanDeviceCapabilities::Layer_const_iterator VulkanDeviceCapabilities::layerBegin()const noexcept
{
    return m_layersProperties.cbegin();
}

VulkanDeviceCapabilities::Layer_const_iterator VulkanDeviceCapabilities::layerEnd()const noexcept
{
    return m_layersProperties.cend();
}

//------------------------------------------------------------------------------------------
VkPresentModeKHR VulkanDeviceCapabilities::bestPresentationMode()const
{
    if(!m_swapChainCapabilities.has_value())
        throw  Exception("Swapchain capabilities not created");
    if (std::find(m_swapChainCapabilities.value().supportedModes.cbegin(), m_swapChainCapabilities.value().supportedModes.cend(), VK_PRESENT_MODE_MAILBOX_KHR) != m_swapChainCapabilities.value().supportedModes.cend())
        return VK_PRESENT_MODE_MAILBOX_KHR;
    return VK_PRESENT_MODE_FIFO_KHR;
}

VkSurfaceFormatKHR VulkanDeviceCapabilities::bestSurfaceFormat()const
{
    if (!m_swapChainCapabilities.has_value())
        throw  Exception("Swapchain capabilities not created");

    // If only 1 format available and is undefined, then this means ALL formats are available (no restrictions)
    if (m_swapChainCapabilities.value().supportedFormats.size() == 1 && m_swapChainCapabilities.value().supportedFormats[0].format == VK_FORMAT_UNDEFINED)
        return{ VK_FORMAT_R8G8B8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };

    // If restricted, search for optimal format
    auto iter = std::find_if(m_swapChainCapabilities.value().supportedFormats.begin(), m_swapChainCapabilities.value().supportedFormats.end(), [&](const auto& format)
        {
            return (format.format == VK_FORMAT_R8G8B8A8_UNORM || format.format == VK_FORMAT_B8G8R8A8_UNORM)
                && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
        });
    if (iter != m_swapChainCapabilities.value().supportedFormats.end())
        return *iter;

    // If can't find optimal format, then just return first format
    return m_swapChainCapabilities.value().supportedFormats[0];
}

void VulkanDeviceCapabilities::getSwapChainCapabilities(const VkSurfaceKHR a_surface)
{
    VulkanSwapchainCapabilities swapChainCapabilities;
    VK_CHECK_EXCEPT(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_physicalDevice, a_surface, &swapChainCapabilities.surfaceCapabilities));

    uint32_t formatCount = 0;
    VK_CHECK_EXCEPT(vkGetPhysicalDeviceSurfaceFormatsKHR(m_physicalDevice, a_surface, &formatCount, nullptr));
    if (formatCount > 0)
    {
        swapChainCapabilities.supportedFormats.resize(static_cast<int>(formatCount));
        VK_CHECK_EXCEPT(vkGetPhysicalDeviceSurfaceFormatsKHR(m_physicalDevice, a_surface, &formatCount, swapChainCapabilities.supportedFormats.data()));
    }

    uint32_t presentCount = 0;
    VK_CHECK_EXCEPT(vkGetPhysicalDeviceSurfacePresentModesKHR(m_physicalDevice, a_surface, &presentCount, nullptr));
    if (presentCount > 0)
    {
        swapChainCapabilities.supportedModes.resize(static_cast<int>(presentCount));
        VK_CHECK_EXCEPT(vkGetPhysicalDeviceSurfacePresentModesKHR(m_physicalDevice, a_surface, &presentCount, swapChainCapabilities.supportedModes.data()));
    }
    m_swapChainCapabilities = swapChainCapabilities;
}