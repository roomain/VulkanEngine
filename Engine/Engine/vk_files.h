#pragma once
#include <string>
#include <vector>
#include "vk_ext_struct.h"

/*@brief loading files*/
namespace Vulkan
{
	/*@brief load binary file and store data into a buffer*/
	void readBinary(const std::string& a_filename, std::vector<char>& a_bin);


	/*@brief engine configuration*/
	struct VulkanConfiguration;

	/*@brief load vulkan configuration*/
	void loadConfiguration(const std::string& a_filename, VulkanConfiguration& a_vulkanConf);
}

