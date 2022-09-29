#pragma once
#include <string>
#include "vk_ext_struct.h"

namespace Vulkan
{
	/*@brief info about host application*/
	struct ApplicationInfo
	{
		std::string appName;
		int appVersion;
	};

	struct RendererProps
	{
		std::vector<const char*> instanceProps;
		std::vector<const char*> instanceLayers;
	};

	/*@brief vulkan renderer*/
	class VK_Renderer
	{
	public:
		static constexpr uint32_t ENGINE_VERSION = 1;

		// LOADING FUNCTIONS
		/*@brief load a shader*/

	private:
		VkInstance m_vulkanInst;
		Device m_device;

		static VK_Renderer* m_pInstance;

		VK_Renderer(const ApplicationInfo& a_appInfo, const RendererProps a_props);
		virtual ~VK_Renderer();
	};
}

