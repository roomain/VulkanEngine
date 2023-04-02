#pragma once
#include <vector>
#include <memory>
#include "vulkan/vulkan.h"


namespace Vulkan
{
	class IDataDisplayer;
	class VK_VulkanCapabilities;
	struct DeviceQueuesConfiguration;
	class VK_WindowSystemProxy;


	/*@brief image format properties*/
	struct FormatProperty
	{
		VkFormat format;				/*!< an image format*/
		VkFormatProperties properties;	/*!< physical device properties for the associated format*/
	};

	/*@brief Swapchain capabilities*/
	struct SwapchainCapabilities
	{
		VkSurfaceCapabilitiesKHR surfaceCapabilities;		/*!< surface properties eg image size / extent*/
		std::vector<VkSurfaceFormatKHR> supportedFormats;	/*!< supported image formats eg RGBA and size of each color*/
		std::vector<VkPresentModeKHR> supportedModes;		/*!< supported presentation modes*/
	};

	/*@brief vulkan device capabilities*/
	class VK_DeviceCapabilities
	{
		friend class VK_VulkanCapabilities;
	private:
		VkPhysicalDevice m_physicalDevice;						/*!< handle to physical device*/
		SwapchainCapabilities m_swapChainCapabilities;			/*!< device swapchain capabilities*/
		VkPhysicalDeviceProperties m_deviceProperties;			/*!< porperties of the device*/
		VkPhysicalDeviceFeatures m_deviceFeatures;				/*!< features supported by device*/
		VkPhysicalDeviceMemoryProperties m_memoryProperties;	/*!< device memory properties*/
		std::vector<VkExtensionProperties> m_extensions;		/*!< device extensions*/
		std::vector<FormatProperty> m_formatsProperties;		/*!< properties for each supported format*/
		std::vector<VkQueueFamilyProperties> m_queueFamilies;	/*!< properties of queue families*/

		VkSurfaceCapabilitiesKHR m_surfaceCapabilities;			/*!< surface properties eg image size / extent*/

		void getFormatsProperties();
		void getSwapChainCapabilities(const VkSurfaceKHR a_surface);
		void displayDeviceproperties(IDataDisplayer& a_displayer)const;
		void displayDeviceQueuesproperties(IDataDisplayer& a_displayer)const;
		void displayDeviceMemoryProperties(IDataDisplayer& a_displayer)const;
		void displayDeviceFeatures(IDataDisplayer& a_displayer)const;
		void displayDeviceFormats(IDataDisplayer& a_displayer)const;
		void displaySwapchain(IDataDisplayer& a_displayer)const;
		void displayDeviceLimits(IDataDisplayer& a_displayer)const;
		void displayDeviceSparseProps(IDataDisplayer& a_displayer)const;

		[[nodiscard]] VK_DeviceCapabilities(const VkPhysicalDevice m_physicalDevice);

	public:
		VK_DeviceCapabilities() = delete;
		~VK_DeviceCapabilities() = default;
		/*@brief display data*/
		void display(IDataDisplayer& a_displayer)const;
		[[nodiscard]] VkPhysicalDevice physicalDevice()const { return m_physicalDevice; }
		/*@brief get the formats which support a_tiling and a_featureFlag (throw anexception if no format found)*/
		[[nodiscard]] void supportedFormat(std::vector<VkFormat>& a_formats, const VkImageTiling a_tiling, const VkFormatFeatureFlags a_featureFlag)const;
		/*@brief get memory type index*/
		[[nodiscard]] uint32_t memoryTypeIndex(uint32_t a_memTypeBits, VkMemoryPropertyFlags a_flags)const;
		/*@brief get best presentation modes*/
		[[nodiscard]] VkPresentModeKHR bestPresentationMode()const;
		/*@brief get best surface format*/
		[[nodiscard]] VkSurfaceFormatKHR bestSurfaceFormat()const;
		/*@brief fill queues index from configuration*/
		void queues(const std::shared_ptr<VK_WindowSystemProxy>& a_pWinProxy, DeviceQueuesConfiguration& a_queueConf)const;
		/*@brief swapchain capabilities*/
		[[nodiscard]] inline const SwapchainCapabilities& swapchainCapabilities()const { return m_swapChainCapabilities; }
	};
}
