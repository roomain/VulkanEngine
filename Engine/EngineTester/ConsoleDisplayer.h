#pragma once
#include "IDisplayer.h"
#include <string>

class ConsoleDisplayer : public Vulkan::IDisplayer
{
private:
    std::string m_linePrefix;

public:
    ConsoleDisplayer() = default;
    void beginNode(const std::string& a_name) override;                                      /*!< begin writing node*/
    void endNode() override;                                                                 /*!< end writing node (return to parent)*/
    void attribute(const std::string& a_name, const std::string& a_value) override;          /*!< set attribude value*/
    void attribute(const std::string& a_name, const int a_value) override;                   /*!< set attribude value*/
    void attribute(const std::string& a_name, const unsigned int a_value) override;          /*!< set attribude value*/
    void attribute(const std::string& a_name, const float a_value) override;                 /*!< set attribude value*/
    void attribute(const std::string& a_name, const double& a_value) override;               /*!< set attribude value*/
    void attribute(const std::string& a_name, const unsigned char a_value) override;         /*!< set attribude value*/
    void attribute(const std::string& a_name, const short a_value) override;                 /*!< set attribude value*/
    void attribute(const std::string& a_name, const unsigned short a_value) override;        /*!< set attribude value*/
    void attribute(const std::string& a_name, const size_t a_value) override;                /*!< set attribude value*/
    void reset();
};