#pragma once

#include "vulkan/vulkan.h"
#include "vk_globals.h"
#include "vk_globals.h"

namespace Vulkan
{
	struct Device;
	struct SwapchainCapabilities;
	struct FormatProperty;
	struct EngineDeviceCapabilities;
	class IDisplayer;

	//--------------------------------------------------------------------------------------------------------------------------
	/*@brief display vulkan instance layer properties*/
	void ENGINE_EXPORT displayInstanceLayerProps(IDisplayer& a_displayer);

	/*@brief display vulkan instance extension properties*/
	void ENGINE_EXPORT displayInstanceExtensionProps(IDisplayer& a_displayer);


	void ENGINE_EXPORT displayVulkanCapabilities(VkInstance a_vulkan, IDisplayer& a_displayer);
	void ENGINE_EXPORT displayDeviceCapabilities(VkInstance a_vulkan, const int a_deviceIndex, IDisplayer& a_displayer);
}