#include "pch.h"
#include "vk_files.h"
#include "vk_Exception.h"
#include <fstream>
#include <format>

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
}