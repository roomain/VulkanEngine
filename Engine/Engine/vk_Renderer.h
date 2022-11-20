#pragma once
#include <string>
#include "vk_files.h"
#include "vk_ext_struct.h"
#include "vk_globals.h"
#include <memory>

#pragma warning(push)
#pragma warning( disable : 4251)

namespace Vulkan
{
	class VK_WindowSystemProxy;
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
		void init(const std::string& a_confFile, VK_Logger* const a_pLogger, const std::vector<std::string> &a_windowSysExtensions, std::vector<PhysicalDeviceInfo>& a_compatibleDevices);
		void startRendering(const unsigned int a_deviceIndex, std::unique_ptr<VK_WindowSystemProxy>&& a_windowProxy);

		/*@brief called when window is resized*/
		void onWindowResized();

		/*@return the vulkan instance*/
		VkInstance vulkanInstance()const noexcept;

	protected:

	private:
		VulkanConfiguration m_vkConf;						/*!< engine configuration*/
		VkInstance m_vulkanInst;							/*!< vulkan instance*/
		Device m_device;									/*!< vulkan used device*/
		EngineDeviceCapabilities m_deviceCapabilities;		/*!< device capabilities*/

		VkSwapchainKHR m_swapChain;							/*!< swapchain*/
		std::vector<BaseImage> m_vSwapchainImages;			/*!< swapchain images*/

		std::unique_ptr<VK_WindowSystemProxy> m_windowProxy;/*!< proxy to window system*/

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

#pragma warning(pop)
