#pragma once
#include "IDataDisplayer.h"
#include "vk_logger.h"
#include <string>

class ConsoleDisplayer : public Vulkan::IDataDisplayer
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

class ConsoleLogger : public Vulkan::VK_Logger
{
public:
    [[nodiscard]] explicit ConsoleLogger(Vulkan::VK_Logger::MessageFilter a_filter = Vulkan::VK_Logger::MessageFilter::None);
    ConsoleLogger(auto&) = delete;

protected:
    void log(const std::string& a_flag, const std::string& a_type, uint64_t a_obj, size_t a_location, int32_t a_code, const char* a_layerPrefix, const char* a_message) override;
};