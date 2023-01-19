#pragma once
#include <memory>
#include <string>
#include <vector>
#include "vulkan/vulkan.h"
#include "vk_globals.h"
#include "vk_macros.h"
#include "vk_capabilities.h"
#include "vk_configuration.h"

namespace Vulkan
{
	class VK_Logger;
	class IDisplayer;
	class VK_Device;
	class VK_WindowSystemProxy;

	/*@brief device short informations*/
	struct DeviceInfo
	{
		const int deviceIndex;	/*!< device index in vulkan instance*/
		std::string name;		/*!< device name*/
		std::string deviceType;	/*!< device type*/
		uint32_t apiVersion;	/*!< API version*/
		uint32_t driverVersion;	/*!< Driver version*/
	};

	/*@brief singleton dealing with vulkan*/
	class ENGINE_EXPORT VK_Application
	{
	private:
		constexpr static uint32_t ENGINE_VERSION = 1;

		static VK_Application* m_pInstance;	/*!< singleton instance*/
		VkInstance m_vulkanInst;			/*!< vulkan instance*/

		InstanceCapabilities m_capabilities;						/*!< vulkan instance capabilities*/
		std::vector<DeviceCapabilities> m_vDeviceCapabilities;		/*!< capabilities for each vulkan device*/
		
		VkDebugReportCallbackEXT m_debugCallbackHandle;								/*!< vulkan debug message handle*/
		static PFN_vkCreateDebugReportCallbackEXT vkCreateDebugReportCallbackEXT;	/*!< create messenger loaded function*/
		static PFN_vkDestroyDebugReportCallbackEXT vkDestroyDebugReportCallbackEXT;	/*!< destroy messenger loaded function*/

		[[nodiscard]] VK_Application();

		// debug function
		static VkBool32 messageCallback(VkDebugReportFlagsEXT flags,				// Type of error
			VkDebugReportObjectTypeEXT objType,			// Type of object causing error
			uint64_t obj,								// ID of object
			size_t location,
			int32_t code,
			const char* layerPrefix,
			const char* message,						// Validation Information
			void* userData);

	public:
		[[nodiscard]] static VK_Application* const instance();
		virtual ~VK_Application();
		
		//----------------------------------------------------------------------
		/*@brief create vulkan instance*/
		void createVulkanInstance(const InstanceConf& a_conf, VK_Logger* const a_pLogger);
		//-----------------------------------------------------------------------
		[[nodiscard]] bool checkInstanceLayer(const std::string& a_layer)const noexcept;
		[[nodiscard]] bool checkInstanceLayers(const std::vector<std::string>& a_vLayer)const noexcept;
		[[nodiscard]] bool checkInstanceExtension(const std::string& a_ext)const noexcept;
		[[nodiscard]] bool checkInstanceExtensions(const std::vector<std::string>& a_vExt)const noexcept;
		//-----------------------------------------------------------------------
		/*@brief display instance capabilities*/
		void displayInstanceCapabilities(IDisplayer& a_displayer)const;
		/*@brief display device capabilities*/
		void displayDevicesCapabilities(IDisplayer& a_displayer)const;
		//--------------------------------------------------------------
		/*@brief search compatible device for configuration*/
		void searchCompatibleDevice(const VulkanConfiguration& a_conf, std::vector<DeviceInfo>& a_vDevice, const std::shared_ptr<VK_WindowSystemProxy>& a_winProxy);
	};
}