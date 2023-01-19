#pragma once
#include "vulkan/vulkan.h"
#include <memory>

namespace Vulkan
{
	/*@brief Provides an interface between windows system and vulkan*/
	/*vulkan engine is independant of a windows system*/
	class VK_WindowSystemProxy
	{
	public:
		virtual ~VK_WindowSystemProxy() {}
		virtual VkSurfaceKHR surface() = 0;
		virtual uint32_t width() = 0;
		virtual uint32_t height() = 0;
		virtual void resetSurface() = 0;
		// TODO
	};

	using VK_WindowSystemProxyUPtr = std::unique_ptr<VK_WindowSystemProxy>;
}