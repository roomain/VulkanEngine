#include "pch.h"
#include "vk_Exception.h"
#include <format>

namespace Vulkan
{
	VK_Exception::VK_Exception(const std::string& a_message, const std::source_location& a_location) : std::exception{ a_message.c_str() }, m_location { a_location }{}

	char const* VK_Exception::what() const
	{
		return std::format("{} in {} at line {}", std::string(std::exception::what()), std::string(m_location.function_name()), std::to_string(m_location.line())).c_str();
	}
}
