#pragma once
#include <exception>
#include <source_location>
#include <string>
#include "vulkan/vulkan.h"
#include "vk_globals.h"


#pragma warning( disable : 4275 )
#pragma warning( disable : 4251 )
#pragma warning( push )

namespace Vulkan
{
	/*@brief vulkan exception*/
	class ENGINE_EXPORT VK_Exception : public std::exception
	{
	private:
		std::source_location m_location; /*!< exception location*/
		std::string m_message;

	public:
		VK_Exception() = delete;
		[[nodiscard]] explicit VK_Exception(const std::string& a_message, const std::source_location& a_location);
		virtual char const* what() const override;
	};

	
}

#pragma warning( pop )

