#include "pch.h"
#include "vk_logger.h"
#include "vk_enum_to_string.h"

namespace Vulkan
{
	VK_Logger::VK_Logger(MessageFilter a_filter) : m_filter{a_filter}{}

	void VK_Logger::log(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* message)
	{
		log(Flag<VkDebugReportFlagBitsEXT>::to_string(flags), to_string(objType), obj, location, code, layerPrefix, message);
	}
	//
}