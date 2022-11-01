#pragma once
#include "vk_globals.h"
#include "vulkan/vulkan.h"

namespace Vulkan
{
	class ENGINE_EXPORT VK_Logger
	{
	public:
		enum class MessageFilter
		{
			None
			//
		};

		VK_Logger(MessageFilter a_filter);

		void log(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* message);
		
	protected:
		virtual void log(const std::string& a_flag, const std::string& a_type, uint64_t a_obj, size_t a_location, int32_t a_code, const char* a_layerPrefix, const char* a_message) = 0;

	private:
		MessageFilter m_filter;
	};
}
