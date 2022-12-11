#pragma once
#include <vector>
#include <string>
#include "vulkan/vulkan.h"
#include "vk_globals.h"


namespace Vulkan
{

	struct RendererQueuesConfiguration;

	/*@brief check if vulkan instance supports layers*/
	[[nodiscard]] bool ENGINE_EXPORT checkInstanceLayerProps(const std::vector<const char*>& a_properties);

	/*@brief check if vulkan instance supports properties and check if debug extension is required*/
	[[nodiscard]] bool ENGINE_EXPORT checkInstanceExtensionProps(const std::vector<const char*>& a_properties, bool& a_hasDebugExt);

	//------------------------------------------------------------------------------------------------------------------

	/*@brief check if vulkan instance supports layers*/
	[[nodiscard]] bool checkInstanceLayerProps(const std::vector<std::string>& a_layers);

	/*@brief check if vulkan instance supports properties and check if debug extension is required*/
	[[nodiscard]] bool checkInstanceExtensionProps(const std::vector<std::string>& a_properties, bool& a_hasDebugExt);

	/*@brief check if physical device support extensions*/
	[[nodiscard]] bool checkPhysicalDeviceExtension(VkPhysicalDevice a_physicalDevice, const std::vector<std::string>& a_extension);

	/*@brief check if physical device support queues configuration*/
	bool checkPhysicalDeviceQueues(VkPhysicalDevice a_physicalDevice, const VkSurfaceKHR a_surface, RendererQueuesConfiguration& a_queueConf);

}