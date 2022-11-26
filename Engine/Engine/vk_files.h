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
	struct VulkanConfiguration
	{
		bool useDepthBuffer;						/*!< use depth buffer*/
		std::string appName;						/*!< application names*/
		int appVersion;								/*!< application version*/
		std::vector<std::string> instanceExtProps;	/*!< vulkan instance extensions properties*/
		std::vector<std::string> instanceLayers;	/*!< vulkan instance desired layer*/
		std::vector<std::string> deviceExt;			/*!< physical device extensions*/
		RendererQueuesConfiguration queues;			/*!< queues configuration*/
	};

	/*@brief load vulkan configuration*/
	void loadConfiguration(const std::string& a_filename, VulkanConfiguration& a_vulkanConf);
}

