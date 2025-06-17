#pragma once
/***********************************************
* @headerfile EngineResizable.h
* @date 27 / 10 / 2024
* @author Roomain
************************************************/
#include <functional>
#include <vector>
#include "EngineObject.h"
#include "Engine_globals.h"

#pragma warning(push)
#pragma warning( disable : 4251 )

/*@base resizable object*/
class VULKAN_ENGINE_LIB EngineResizable : public EngineObject
{
protected:
    virtual void internalResize(const unsigned int a_width, const unsigned int a_height) = 0;

public:
    EngineResizable() = default;
    virtual  ~EngineResizable() = default;
    virtual [[nodiscard]] uint32_t width() const = 0;
    virtual [[nodiscard]] uint32_t height() const = 0;
    void onResize(const unsigned int a_width, const unsigned int a_height);
};

#pragma warning(pop)