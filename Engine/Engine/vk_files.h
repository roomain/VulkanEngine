#pragma once
#include <string>
#include <vector>

/*@brief loading files*/
namespace Vulkan
{
	/*@brief load binary file and store data into a buffer*/
	void readBinary(const std::string& a_filename, std::vector<char>& a_bin);
}

