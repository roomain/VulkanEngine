#pragma once
/***********************************************
* @headerfile VulkanCapabilities.h
* @date 06 / 10 / 2024
* @author Roomain
************************************************/
#include <vector>
#include <unordered_map>
#include "vulkan/vulkan.h"
#include "common/notCopiable.h"
#include "VulkanDeviceCapabilities.h"
#include "Engine_globals.h"

#pragma warning(push)
#pragma warning( disable : 4251 )

struct VulkanDeviceParameter;

class VULKAN_ENGINE_LIB VulkanCapabilities
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

    /*@brief compatible queues configuration for a device*/
    struct VulkanDeviceQueuesConf
    {
        std::vector<VkDeviceQueueCreateInfo> baseCreateInfo;    /*!< queues configurations*/
        std::vector<float> priorities;                          /*!< queues priorities*/
    };

    /*@brief Queues configuration per device index*/
    using VulkanDeviceConfMap = std::unordered_map<int, VulkanDeviceQueuesConf>;

    void findDeviceCompatibleConfiguration(const VulkanDeviceParameter& a_parameters, VulkanDeviceConfMap& a_conf, VkSurfaceKHR a_surface)const;
};


#pragma warning(pop)