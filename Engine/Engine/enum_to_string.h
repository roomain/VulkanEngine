#pragma once

#include <string>

#define BEGIN_ENUM_TO_STRING(Type) \
static inline std::string to_string(const Type a_value) \
{ \
    std::string strValue = #Type; \
    switch(a_value) \
    {

#define ENUM_TO_STRING(value) \
    case value: \
        strValue += "::" + #value; \
        break;


#define END_ENUM_TO_STRING \
    } \
    return strValue; \
}