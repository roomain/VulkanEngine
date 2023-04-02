#pragma once
#include <memory>
#include <string>
#include <vector>
#include "vulkan/vulkan.h"
#include "vk_globals.h"
#include "vk_macros.h"
#include "vk_configuration.h"

namespace Vulkan
{
	class VK_Logger;
	class IDataDisplayer;
	class VK_Device;
	class VK_Renderer;
	class VK_WindowSystemProxy;
	struct DeviceInfo;
	

	/*@brief singleton dealing with vulkan*/
	class ENGINE_EXPORT VK_Application
	{
	private:
		constexpr static uint32_t ENGINE_VERSION = 1;

		static VK_Application* m_pInstance;	/*!< singleton instance*/
		VkInstance m_vulkanInst;			/*!< vulkan instance*/

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
		VK_Application(const VK_Application& ) = delete;
		VK_Application& operator = (const VK_Application&) = delete;

		[[nodiscard]] static VK_Application* const instance();
		virtual ~VK_Application();
		constexpr VkInstance vulkanInstance()const { return m_vulkanInst; }
		//----------------------------------------------------------------------
		/*@brief create vulkan instance*/
		void createVulkanInstance(const InstanceConf& a_conf, VK_Logger* const a_pLogger);

		//--------------------------------------------------------------

		[[nodiscard]] std::shared_ptr<VK_Renderer> createRenderer(const VulkanConfiguration& a_conf, const DeviceInfo& a_chosenDevice, const std::shared_ptr<VK_WindowSystemProxy>& a_winProxy)const;
	};
}