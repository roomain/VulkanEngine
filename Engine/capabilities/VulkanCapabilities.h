#pragma once
/***********************************************
* @headerfile VulkanCapabilities.h
* @date 06 / 10 / 2024
* @author Roomain
************************************************/
#include <vector>
#include "vulkan/vulkan.h"
#include "common/notCopiable.h"
#include "VulkanDeviceCapabilities.h"

class VulkanCapabilities
{
private:
    VkInstance m_instance;                              /*!< vulkan instance*/
    std::vector<VkExtensionProperties> m_extensions;    /*!< instance extension properties*/
    std::vector<VkLayerProperties> m_layers;            /*!< instance layer properties*/
    std::vector<VulkanDeviceCapabilities> m_devices;    /*!< devices capabilities*/

public:
    VulkanCapabilities();
    ~VulkanCapabilities() = default;
    NOT_COPIABLE(VulkanCapabilities)

    using Extension_const_iterator = std::vector<VkExtensionProperties>::const_iterator;
    [[nodiscard]] Extension_const_iterator extensionBegin()const noexcept;
    [[nodiscard]] Extension_const_iterator extensionEnd()const noexcept;

    using Layer_const_iterator = std::vector<VkLayerProperties>::const_iterator;
    [[nodiscard]] Layer_const_iterator layerBegin()const noexcept;
    [[nodiscard]] Layer_const_iterator layerEnd()const noexcept;

    using Device_const_iterator = std::vector<VulkanDeviceCapabilities>::const_iterator;
    [[nodiscard]] Device_const_iterator deviceBegin()const noexcept;
    [[nodiscard]] Device_const_iterator deviceEnd()const noexcept;
};

