#pragma once
#include "vulkan/vulkan.h"
#include "vk_Exception.h"
#include "vk_enum_to_string.h"


#ifdef _DEBUG
#define VK_CHECK(funRes) \
if(funRes != VK_SUCCESS) \
{\
	throw Vulkan::VK_Exception(to_string(static_cast<VkResult>(funRes)) + " for call " + #funRes, std::source_location::current()); \
}
#else
#define VK_CHECK(funRes)
#endif

#define FLAG_OPERATOR(enumerator) \
constexpr enumerator operator | (const enumerator a_first, const enumerator a_second)\
{\
	return static_cast<enumerator>(static_cast<unsigned int>(a_first) | static_cast<unsigned int>(a_second));\
}\
\
constexpr enumerator operator & (const enumerator a_first, const enumerator a_second)\
{\
	return static_cast<enumerator>(static_cast<unsigned int>(a_first) & static_cast<unsigned int>(a_second)); \
}\
\
constexpr enumerator operator ~ (const enumerator a_enum)\
{\
	return static_cast<enumerator>(~static_cast<unsigned int>(a_enum)); \
}
