#include "pch.h"
#include "localLogger.h"

void LocalLogger::init(const LogFun& a_info, 
                    const LogFun& a_warning, 
                    const LogFun& a_error, 
                    const LogFun& a_critical)
{
    m_info = a_info;
    m_warning = a_warning;
    m_error = a_error;
    m_critical = a_critical;
}

void LocalLogger::info(const std::string& a_message, const std::source_location& a_location)
{
    if(m_info)
        m_info(a_message, a_location);
}

void LocalLogger::warning(const std::string& a_message, const std::source_location& a_location)
{
    if(m_warning)
        m_warning(a_message, a_location);
}

void LocalLogger::error(const std::string& a_message, const std::source_location& a_location)
{
    if(m_error)
        m_error(a_message, a_location);
}

void LocalLogger::critical(const std::string& a_message, const std::source_location& a_location)
{
    if(m_critical)
        m_critical(a_message, a_location);
}