#pragma once
/***********************************************
* @headerfile EngineObject.h
* @date 27 / 10 / 2024
* @author Roomain
************************************************/
#include <functional>
#include <vector>
#include "Engine_globals.h"

#pragma warning(push)
#pragma warning( disable : 4251 )
class EngineObject;

using CallbackDelete = std::function<void(const EngineObject*)>;

/*@brief base engine object*/
class VULKAN_ENGINE_LIB EngineObject
{
private:
    std::vector<CallbackDelete> m_vDeleteCallback;  /*!< callback delete object*/

public:
    EngineObject() = default;
    ~EngineObject();
    void registerCallback(const CallbackDelete& a_callback);
    void unregisterCallback(const CallbackDelete& a_callback);
};
#pragma warning(pop)