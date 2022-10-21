#include "pch.h"
#include "vk_files.h"
#include "vk_Exception.h"
#include "vk_string_to_enum.h"
#include <fstream>
#include <format>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

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

	void loadConfiguration(const std::string& a_filename, VulkanConfiguration& a_vulkanConf)
	{
		boost::property_tree::ptree propTree;
		boost::property_tree::xml_parser::read_xml(a_filename, propTree);

		auto treeApp = propTree.get_child("Engine_configuration.vk_application");
		a_vulkanConf.appName = treeApp.get<std::string>("<xmlattr>.name");
		a_vulkanConf.appVersion = treeApp.get<int>("<xmlattr>.version");


		auto treeInstance = propTree.get_child("Engine_configuration.vk_instance");
		for (auto item : treeInstance.get_child("vk_layers"))
		{
			if(item.first.compare("vk_layer") == 0)
				a_vulkanConf.instanceLayers.emplace_back(item.second.data());
		}

		for (auto item : treeInstance.get_child("vk_extensions"))
		{
			if (item.first.compare("vk_extension") == 0)
				a_vulkanConf.instanceExtProps.emplace_back(item.second.data());
		}
		//propTree.get_child_optional("Window.Pos");
	}
}