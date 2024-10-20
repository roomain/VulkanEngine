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
#include "vulkan/vulkan.h"

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


class VulkanDeviceCapabilities
{
    friend class VulkanCapabilities;
private:
    uint32_t m_deviceIndex;                                                 /*!< device index*/
	VkPhysicalDevice m_physicalDevice;						                /*!< handle to physical device*/
    std::optional<VulkanSwapchainCapabilities> m_swapChainCapabilities;     /*!< swap chain capabilities*/
	VkPhysicalDeviceProperties m_deviceProperties;			                /*!< porperties of the device*/
	VkPhysicalDeviceFeatures m_deviceFeatures;				                /*!< features supported by device*/
	std::vector<VkExtensionProperties> m_extensions;		                /*!< device extensions*/
    std::vector<VkLayerProperties> m_layersProperties;                      /*!< device layer properties*/
	VkPhysicalDeviceMemoryProperties m_memoryProperties;	                /*!< device memory properties*/
	std::unordered_map<VkFormat, VkFormatProperties> m_formatsCapabilities;	/*!< Capabilities for each supported format*/
	std::vector<VkQueueFamilyProperties> m_queueFamilies;	                /*!< Capabilities of queue families*/

    explicit VulkanDeviceCapabilities(const uint32_t a_deviceIndex, const VkPhysicalDevice a_device);
    
public:
    VulkanDeviceCapabilities() = delete;
    ~VulkanDeviceCapabilities() = default;

	[[nodiscard]] VkPhysicalDevice physicalDevice()const;
    [[nodiscard]] VulkanDeviceInfo deviceInfo()const;
    void supportedFormats(std::vector<VkFormat>& a_vFormat)const;
    [[nodiscard]] const VkFormatProperties formatProperties(const VkFormat a_format)const;
    [[nodiscard]] const std::optional<VulkanSwapchainCapabilities> swapchainCapabilties()const;

    using Queue_const_iterator = std::vector<VkQueueFamilyProperties>::const_iterator;
    [[nodiscard]] Queue_const_iterator queueBegin()const noexcept;
    [[nodiscard]] Queue_const_iterator queueEnd()const noexcept;

    using Extension_const_iterator = std::vector<VkExtensionProperties>::const_iterator;
    [[nodiscard]] Extension_const_iterator extensionBegin()const noexcept;
    [[nodiscard]] Extension_const_iterator extensionEnd()const noexcept;

    using Layer_const_iterator = std::vector<VkLayerProperties>::const_iterator;
    [[nodiscard]] Layer_const_iterator layerBegin()const noexcept;
    [[nodiscard]] Layer_const_iterator layerEnd()const noexcept;

    //------------------------------------------------------------------------------------------
    /*@brief get best presentation modes*/
	[[nodiscard]] VkPresentModeKHR bestPresentationMode()const;
	/*@brief get best surface format*/
	[[nodiscard]] VkSurfaceFormatKHR bestSurfaceFormat()const;
    void getSwapChainCapabilities(const VkSurfaceKHR a_surface);

};