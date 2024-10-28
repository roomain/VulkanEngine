#include "pch.h"
#include <algorithm>
#include "EngineResizable.h"


void EngineResizable::registerCallback(const CallbackResize&  /*a_callback*/)
{
    // todo
}

void EngineResizable::unregisterCallback(const CallbackResize& /*a_callback*/)
{
    // todo
}


void EngineResizable::onResize(const unsigned int a_width, const unsigned int a_height)
{
    internalResize(a_width, a_height);
    // todo
}