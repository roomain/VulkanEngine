#pragma once
#include <vector>
#include <string>
#include "vulkan/vulkan.h"
#include "vk_globals.h"


namespace Vulkan
{

	struct RendererQueuesConfiguration;

	/*@brief check if vulkan instance supports layers*/
	bool ENGINE_EXPORT checkInstanceLayerProps(const std::vector<const char*>& a_properties);

	/*@brief check if vulkan instance supports properties and check if debug extension is required*/
	bool ENGINE_EXPORT checkInstanceExtensionProps(const std::vector<const char*>& a_properties, bool& a_hasDebugExt);

	//------------------------------------------------------------------------------------------------------------------

	/*@brief check if vulkan instance supports layers*/
	bool checkInstanceLayerProps(const std::vector<std::string>& a_layers);

	/*@brief check if vulkan instance supports properties and check if debug extension is required*/
	bool checkInstanceExtensionProps(const std::vector<std::string>& a_properties, bool& a_hasDebugExt);

	/*@brief check if phydical device support queues configuration and extensions, fill render queues configuration indices*/
	bool checkPhysicalDeviceForCapabilities(VkPhysicalDevice a_physicalDevice, RendererQueuesConfiguration& a_queueConf, const std::vector<std::string>& a_extension);
}