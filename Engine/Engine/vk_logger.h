#pragma once
#include <vulkan/vulkan.h>

namespace Vulkan
{
	class VK_Logger
	{
	public:
		VK_Logger& operator << (const VkResult a_data);
		VK_Logger& operator << (const VkStructureType a_data);
		VK_Logger& operator << (const VkObjectType a_data);
		VK_Logger& operator << (const VkDebugUtilsMessageSeverityFlagBitsEXT a_data);
		VK_Logger& operator << (const VkDebugUtilsMessageTypeFlagsEXT a_data);
		//virtual void  log();
		//
	};
}