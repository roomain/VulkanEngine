#pragma  once
#include <string>
#include "vulkan/vulkan.h"

namespace Vulkan
{
    /*@brief interface class to display device capabilities organized in tree*/
    class IDisplayer
    {
    public:
        virtual void beginChildren() = 0; /*!< begin writing children*/
        virtual void endChildren() = 0; /*!< end writing children (return to parent)*/
        virtual void operator << (const std::string& a_value) = 0;
        virtual void operator << (const int a_value) = 0;
        virtual void operator << (const float a_value) = 0;
        virtual void operator << (const double& a_value) = 0;
        //
    };
}