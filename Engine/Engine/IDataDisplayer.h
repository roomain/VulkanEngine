#pragma  once
#include <string>
#include "vk_globals.h"

namespace Vulkan
{
    /*@brief interface class to display device capabilities organized in tree*/
    class ENGINE_EXPORT IDataDisplayer
    {
    public:
        virtual void beginNode(const std::string& a_name) = 0;                                      /*!< begin writing node*/
        virtual void endNode() = 0;                                                                 /*!< end writing node (return to parent)*/
        virtual void attribute(const std::string& a_name, const std::string& a_value) = 0;          /*!< set attribude value*/
        virtual void attribute(const std::string& a_name, const int a_value) = 0;                   /*!< set attribude value*/
        virtual void attribute(const std::string& a_name, const unsigned int a_value) = 0;          /*!< set attribude value*/
        virtual void attribute(const std::string& a_name, const float a_value) = 0;                 /*!< set attribude value*/
        virtual void attribute(const std::string& a_name, const double& a_value) = 0;               /*!< set attribude value*/
        virtual void attribute(const std::string& a_name, const unsigned char a_value) = 0;         /*!< set attribude value*/
        virtual void attribute(const std::string& a_name, const short a_value) = 0;                 /*!< set attribude value*/
        virtual void attribute(const std::string& a_name, const unsigned short a_value) = 0;        /*!< set attribude value*/
        virtual void attribute(const std::string& a_name, const size_t a_value) = 0;                /*!< set attribude value*/
    };
}