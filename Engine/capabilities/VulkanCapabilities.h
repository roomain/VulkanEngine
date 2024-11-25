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
    static std::vector<VkExtensionProperties> m_instanceExt;    /*!< instance extension properties*/
    static std::vector<VkLayerProperties> m_instanceLay;        /*!< instance layer properties*/
    VkInstance m_instance;                                      /*!< vulkan instance*/
    std::vector<VulkanDeviceCapabilities> m_devices;            /*!< devices capabilities*/

    static void initInstanceExt()noexcept;
    static void initInstanceLay()noexcept;

public:
    VulkanCapabilities() = delete;
    ~VulkanCapabilities() = default;
    explicit VulkanCapabilities(VkInstance a_instance);
    NOT_COPIABLE(VulkanCapabilities)

    using Extension_const_iterator = std::vector<VkExtensionProperties>::const_iterator;
    [[nodiscard]]static Extension_const_iterator extensionBegin()noexcept;
    [[nodiscard]]static Extension_const_iterator extensionEnd()noexcept;

    using Layer_const_iterator = std::vector<VkLayerProperties>::const_iterator;
    [[nodiscard]] static Layer_const_iterator layerBegin()noexcept;
    [[nodiscard]] static Layer_const_iterator layerEnd()noexcept;

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