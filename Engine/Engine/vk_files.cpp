#include "pch.h"
#include <fstream>
#include <format>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <functional>
#include "vk_files.h"
#include "vk_Exception.h"
#include "vk_string_to_enum.h"
#include "vk_configuration.h"

namespace Vulkan
{
	void readBinary(const std::string& a_filename, std::vector<char>& a_bin)
	{
		// Open stream from given file
		// std::ios::binary tells stream to read file as binary
		// std::ios::ate tells stream to start reading from end of file
		std::ifstream file(a_filename, std::ios::binary | std::ios::ate);
		
		if (!file.is_open())
			throw VK_Exception(std::format("Can't open file {}", a_filename), std::source_location::current());

		// Get current read position and use to resize file buffer
		size_t fileSize = (size_t)file.tellg();
		a_bin.resize(fileSize);

		// Move read position (seek to) the start of the file
		file.seekg(0);

		// Read the file data into the buffer (stream "fileSize" in total)
		file.read(a_bin.data(), fileSize);

		// Close stream
		file.close();
	}

	void getDataList(boost::property_tree::ptree& a_parent, const std::string& a_tag, std::vector<std::string>& a_toFill)
	{
		for (const auto& [first, sec] : a_parent.get_child(a_tag))
		{
			a_toFill.emplace_back(sec.data());
		}
	}

	void getDataList(boost::property_tree::ptree& a_parent, const std::string& a_tag, std::function<void (const std::string&)> a_fun)
	{
		for (const auto& [first, sec] : a_parent.get_child(a_tag))
		{
			a_fun(sec.data());
		}
	}

	void loadConfiguration(const std::string& a_filename, VulkanConfiguration& a_vulkanConf)
	{
		a_vulkanConf.useDepthBuffer = false;
		boost::property_tree::ptree propTree;
		boost::property_tree::xml_parser::read_xml(a_filename, propTree);

		auto treeApp = propTree.get_child("Engine_configuration.vk_application");
		a_vulkanConf.appName = treeApp.get<std::string>("<xmlattr>.name");
		a_vulkanConf.appVersion = treeApp.get<int>("<xmlattr>.version");

		auto treeInstance = propTree.get_child("Engine_configuration.vk_instance");
		getDataList(treeInstance, "vk_layers", a_vulkanConf.instanceLayers);
		getDataList(treeInstance, "vk_extensions", a_vulkanConf.instanceExtProps);

		//Device
		auto treeDevice = propTree.get_child("Engine_configuration.vk_device");
		a_vulkanConf.useDepthBuffer = treeDevice.get<bool>("<xmlattr>.useDepthBuffer", false);
		a_vulkanConf.frameTimeout = treeDevice.get<uint64_t>("<xmlattr>.timeout", 2000000000);
		getDataList(treeDevice, "vk_queues", [&](const std::string& value)
			{
				QueueConfiguration conf{ .index = -1 };
				if (to_flag(value, static_cast<VkQueueFlagBits>(0), conf.type))
				{
					a_vulkanConf.queues.vQueueConf.emplace_back(std::move(conf));
				}
				else
				{
					throw VK_Exception("Wrong queue flag", std::source_location::current());
				}
			});
		getDataList(treeDevice, "vk_extensions", a_vulkanConf.deviceExt);

	}
}