#pragma once
#include <string>
#include "vk_ext_struct.h"
#include "vk_globals.h"

namespace Vulkan
{
	class ENGINE_EXPORT VK_Logger;

	/*@brief info about host application*/
	struct ApplicationInfo
	{
		std::string appName;	/*!< application names*/
		int appVersion;			/*!< application version*/
	};

	struct RendererProps
	{
		std::vector<const char*> instanceProps;		/*!< vulkan instance desired properties*/
		std::vector<const char*> instanceLayers;	/*!< vulkan instance desired layer*/
	};

	/*@brief vulkan renderer*/
	class ENGINE_EXPORT VK_Renderer
	{
	public:
		VK_Renderer(const ApplicationInfo& a_appInfo, const RendererProps& a_props, VK_Logger* const a_pLogger);
		virtual ~VK_Renderer();
		void createDevice(const unsigned int a_deviceIndex);

		/*@return the vulkan instance*/
		VkInstance vulkanInstance()const noexcept;

	protected:
		// -- Choose Functions
		virtual void setupQueueConfiguration(const std::vector<VkQueueFamilyProperties>& a_queuesProperties, RendererQueuesConfiguration& a_queueConf)const;

	private:
		VkInstance m_vulkanInst;							/*!< vulkan instance*/
		Device m_device;									/*!< vulkan used device*/
		EngineDeviceCapabilities m_deviceCapabilities;		/*!< device capabilities*/



		VkDebugReportCallbackEXT m_debugCallbackHandle;	/*!< vulkan debug message handle*/




		static constexpr uint32_t ENGINE_VERSION = 1;								/*!< engine version*/
		static PFN_vkCreateDebugReportCallbackEXT vkCreateDebugReportCallbackEXT;	/*!< create messenger loaded function*/
		static PFN_vkDestroyDebugReportCallbackEXT vkDestroyDebugReportCallbackEXT;	/*!< destroy messenger loaded function*/

		/*@brief vulkan message callback*/
		static VKAPI_ATTR VkBool32 messageCallback(VkDebugReportFlagsEXT flags,				// Type of error
			VkDebugReportObjectTypeEXT objType,			// Type of object causing error
			uint64_t obj,								// ID of object
			size_t location,
			int32_t code,
			const char* layerPrefix,
			const char* message,						// Validation Information
			void* userData);

	};
}

