#pragma once
#include <string>
#include "vk_files.h"
#include "vk_ext_struct.h"
#include "vk_globals.h"

namespace Vulkan
{
	class VK_Logger;
	struct VulkanConfiguration;

	struct PhysicalDeviceInfo
	{
		int index;			/*!< index of device*/
		std::string name;	/*!< device name*/
	};

	/*@brief vulkan renderer*/
	class ENGINE_EXPORT VK_Renderer
	{
	public:
		VK_Renderer();
		virtual ~VK_Renderer();
		void init(const std::string& a_confFile, VK_Logger* const a_pLogger, std::vector<PhysicalDeviceInfo>& a_compatibleDevices);
		void createDevice(const unsigned int a_deviceIndex, const uint32_t a_width, const uint32_t a_height);

		/*@return the vulkan instance*/
		VkInstance vulkanInstance()const noexcept;

	protected:

	private:
		VulkanConfiguration m_vkConf;						/*!< engine configuration*/
		VkInstance m_vulkanInst;							/*!< vulkan instance*/
		Device m_device;									/*!< vulkan used device*/
		EngineDeviceCapabilities m_deviceCapabilities;		/*!< device capabilities*/

		// Rendering image size
		uint32_t m_uiWidth;
		uint32_t m_uiHeight;

		// VULKAN DEBUGGING -----------------------------------------------------------------------------
		VkDebugReportCallbackEXT m_debugCallbackHandle;								/*!< vulkan debug message handle*/
		static PFN_vkCreateDebugReportCallbackEXT vkCreateDebugReportCallbackEXT;	/*!< create messenger loaded function*/
		static PFN_vkDestroyDebugReportCallbackEXT vkDestroyDebugReportCallbackEXT;	/*!< destroy messenger loaded function*/

		// DEBUG FUNCTIONS ------------------------------------------------------------------------------
		/*@brief vulkan message callback*/
		static VKAPI_ATTR VkBool32 messageCallback(VkDebugReportFlagsEXT flags,				// Type of error
			VkDebugReportObjectTypeEXT objType,			// Type of object causing error
			uint64_t obj,								// ID of object
			size_t location,
			int32_t code,
			const char* layerPrefix,
			const char* message,						// Validation Information
			void* userData);

		void release();
	};
}

