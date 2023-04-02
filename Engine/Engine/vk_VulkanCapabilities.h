#pragma once
#include <memory>
#include <vector>
#include "vk_InstanceCapabilities.h"
#include "vk_DeviceCapabilities.h"

namespace Vulkan
{
	class VK_WindowSystemProxy;

	/*@brief device short informations*/
	struct DeviceInfo
	{
		uint32_t deviceIndex;	/*!< device index in vulkan instance*/
		std::string name;		/*!< device name*/
		std::string deviceType;	/*!< device type*/
		uint32_t apiVersion;	/*!< API version*/
		uint32_t driverVersion;	/*!< Driver version*/
	};

	/*@brief singleton vulkan capabilities*/
	class VK_VulkanCapabilities
	{
	private:
		VK_InstanceCapabilities m_instanceCapabilities;				/*!< vulkan instance capabilities*/
		std::vector<VK_DeviceCapabilities> m_vDeviceCapabilities;	/*!< vulkan physical devices capabilities*/

		static VK_VulkanCapabilities m_instance;

		VK_VulkanCapabilities();

	public:
		VK_VulkanCapabilities(const VK_VulkanCapabilities&) = delete;
		VK_VulkanCapabilities& operator = (const VK_VulkanCapabilities&) = delete;
		
		~VK_VulkanCapabilities() = default;
		static [[nodiscard]] VK_VulkanCapabilities& instance();
		/*@brief Get instance capabilities*/
		inline const VK_InstanceCapabilities& instanceCapabilities()const { return m_instanceCapabilities; }
		/*@brief enumerate physical device. Return number of devices*/
		uint32_t enumerateDeviceCapabilities(const VkInstance a_instance);
		/*@brief display capabilities*/
		void display(IDataDisplayer& a_displayer)const;

		using DevCapIterator = std::vector<VK_DeviceCapabilities>::const_iterator;
		[[nodiscard]] DevCapIterator cbegin()const { return m_vDeviceCapabilities.cbegin(); }
		[[nodiscard]] DevCapIterator cend()const { return m_vDeviceCapabilities.cend(); }
		[[nodiscard]] inline const VK_DeviceCapabilities& operator[] (const uint32_t a_index)const { return m_vDeviceCapabilities[a_index]; }
		/*@brief search compatibles devices*/
		void searchCompatibleDevice(const VulkanConfiguration& a_conf, const std::shared_ptr<VK_WindowSystemProxy>& a_pWinProxy, std::vector<DeviceInfo>& a_vDevice);
	};
}

