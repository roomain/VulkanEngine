#include "pch.h"
#include "vk_logger.h"
#include "vk_enum_to_string.h"

namespace Vulkan
{
	VK_Logger& VK_Logger::operator << (const VkResult a_data)
	{
		//
		return *this;
	}

	VK_Logger& VK_Logger::operator << (const VkStructureType a_data)
	{
		//
		return *this;
	}

	VK_Logger& VK_Logger::operator << (const VkObjectType a_data)
	{
		//
		return *this;
	}

	VK_Logger& VK_Logger::operator << (const VkDebugUtilsMessageSeverityFlagBitsEXT a_data)
	{
		//
		return *this;
	}

	VK_Logger& VK_Logger::operator << (const VkDebugUtilsMessageTypeFlagsEXT a_data)
	{
		//
		return *this;
	}
}