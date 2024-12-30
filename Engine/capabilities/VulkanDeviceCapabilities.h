#pragma once
/***********************************************
* @headerfile VulkanDeviceCapabilities.h
* @date 05 / 10 / 2024
* @author Roomain
************************************************/

#include <string>
#include <vector>
#include <unordered_map>
#include <optional>
#include <memory>
#include "vulkan/vulkan.h"
#include "Engine_globals.h"

#pragma warning(push)
#pragma warning( disable : 4251 )

struct VulkanDeviceInfo
{
    uint32_t deviceIndex;	/*!< device index in vulkan instance*/
	std::string name;		/*!< device name*/
	std::string deviceType;	/*!< device type*/
	uint32_t apiVersion;	/*!< API version*/
	uint32_t driverVersion;	/*!< Driver version*/
};

struct VulkanSwapchainCapabilities
{
    VkSurfaceCapabilitiesKHR surfaceCapabilities;		/*!< surface properties eg image size / extent*/
    std::vector<VkSurfaceFormatKHR> supportedFormats;	/*!< supported image formats eg RGBA and size of each color*/
    std::vector<VkPresentModeKHR> supportedModes;		/*!< supported presentation modes*/
};

struct VulkanDeviceFeatures;


/*@brief get device capabilities*/
struct VULKAN_ENGINE_LIB VulkanDeviceCapabilities
{
    uint32_t m_deviceIndex;  /*!< device index*/
    std::optional<VulkanSwapchainCapabilities> m_swapChainCapabilities;     /*!< swap chain capabilities*/
    VkPhysicalDeviceProperties m_deviceProperties;			                /*!< porperties of the device*/
    VkPhysicalDeviceFeatures m_deviceFeatures;				                /*!< features supported by device*/
    std::vector<VkExtensionProperties> m_extensions;		                /*!< device extensions*/
    std::vector<VkLayerProperties> m_layersProperties;                      /*!< device layer properties*/
    VkPhysicalDeviceMemoryProperties m_memoryProperties;	                /*!< device memory properties*/
    std::unordered_map<VkFormat, VkFormatProperties> m_formatsCapabilities;	/*!< Capabilities for each supported format*/
    std::vector<VkQueueFamilyProperties> m_queueFamilies;	                /*!< Capabilities of queue families*/

    VulkanDeviceCapabilities() = delete;
    VulkanDeviceCapabilities(const uint32_t a_deviceIndex, const VkPhysicalDevice a_device);
    [[nodiscard]] VulkanDeviceInfo deviceInfo()const;
    /*@brief check features validity*/
    [[nodiscard]] bool isFeaturesAvailable(const VulkanDeviceFeatures& a_features)const;
    static [[nodiscard]] VkPhysicalDeviceFeatures toFeatures(const VulkanDeviceFeatures& a_features);
    /*@brief get best presentation modes*/
    [[nodiscard]] VkPresentModeKHR bestPresentationMode()const;
    [[nodiscard]] VkSurfaceFormatKHR bestSurfaceFormat()const;
    void findQueues(const bool a_presentation, const VkQueueFlags a_flags, std::vector<int>& a_queuesIndex, VkPhysicalDevice a_physicalDevice = VK_NULL_HANDLE, VkSurfaceKHR a_surface = VK_NULL_HANDLE)const;
};

using VulkanDeviceCapabilitiesPtr = std::shared_ptr<VulkanDeviceCapabilities>;
using VulkanDeviceCapabilitiesWPtr = std::weak_ptr<VulkanDeviceCapabilities>;


#pragma warning(pop)