#include "ConsoleDisplayer.h"
#include <iostream>


void ConsoleDisplayer::beginNode(const std::string& a_name)
{
	std::cout << m_linePrefix << a_name << std::endl;
	m_linePrefix += '\t';
}

void ConsoleDisplayer::endNode()
{
	std::cout << std::endl;

	if(!m_linePrefix.empty())
		m_linePrefix.pop_back();
}

void ConsoleDisplayer::attribute(const std::string& a_name, const std::string& a_value)
{
	std::cout << m_linePrefix << a_name << " : " << a_value << std::endl;
}

void ConsoleDisplayer::attribute(const std::string& a_name, const int a_value)
{
	std::cout << m_linePrefix << a_name << " : " << a_value << std::endl;
}

void ConsoleDisplayer::attribute(const std::string& a_name, const unsigned int a_value)
{
	std::cout << m_linePrefix << a_name << " : " << a_value << std::endl;
}

void ConsoleDisplayer::attribute(const std::string& a_name, const float a_value)
{
	std::cout << m_linePrefix << a_name << " : " << a_value << std::endl;
}

void ConsoleDisplayer::attribute(const std::string& a_name, const double& a_value)
{
	std::cout << m_linePrefix << a_name << " : " << a_value << std::endl;
}

void ConsoleDisplayer::attribute(const std::string& a_name, const unsigned char a_value)
{
	std::cout << m_linePrefix << a_name << " : " << a_value << std::endl;
}

void ConsoleDisplayer::attribute(const std::string& a_name, const short a_value)
{
	std::cout << m_linePrefix << a_name << " : " << a_value << std::endl;
}

void ConsoleDisplayer::attribute(const std::string& a_name, const unsigned short a_value)
{
	std::cout << m_linePrefix << a_name << " : " << a_value << std::endl;
}

void ConsoleDisplayer::attribute(const std::string& a_name, const size_t a_value)
{
	std::cout << m_linePrefix << a_name << " : " << a_value << std::endl;
}

void ConsoleDisplayer::reset()
{
	m_linePrefix = "";
}

ConsoleLogger::ConsoleLogger(Vulkan::VK_Logger::MessageFilter a_filter) : Vulkan::VK_Logger(a_filter)
{
	//
}

void ConsoleLogger::log(const std::string& a_flag, const std::string& a_type, uint64_t a_obj, size_t a_location, int32_t a_code, const char* a_layerPrefix, const char* a_message)
{
	std::cerr << "--------------------------------------" << std::endl;
	std::cerr << "Flag: " << a_flag << std::endl;
	std::cerr << "Type: " << a_type << std::endl;
	std::cerr << "Layer: " << a_layerPrefix << std::endl;
	std::cerr << "Message: " << a_message << std::endl;
}