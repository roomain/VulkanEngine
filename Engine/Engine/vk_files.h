#pragma once
#include <string>
#include <vector>
#include "vk_ext_struct.h"
#include "vk_globals.h"

/*@brief loading files*/
namespace Vulkan
{
	/*@brief load binary file and store data into a buffer*/
	ENGINE_EXPORT void readBinary(const std::string& a_filename, std::vector<char>& a_bin);


	/*@brief engine configuration*/
	struct VulkanConfiguration;

	/*@brief load vulkan configuration*/
	ENGINE_EXPORT void loadConfiguration(const std::string& a_filename, VulkanConfiguration& a_vulkanConf);
}

