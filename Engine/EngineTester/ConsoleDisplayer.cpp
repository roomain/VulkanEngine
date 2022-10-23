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