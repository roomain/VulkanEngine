#pragma once
#include <vector>
#include "vk_globals.h"


namespace Vulkan
{
	bool ENGINE_EXPORT checkInstanceLayerProps(const std::vector<const char*>& a_properties);

	bool ENGINE_EXPORT checkInstanceExtensionProps(const std::vector<const char*>& a_properties, bool& a_hasDebugExt);

}