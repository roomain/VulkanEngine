#include "pch.h"
#include <algorithm>
#include "EngineResizable.h"


void EngineResizable::onResize(const unsigned int a_width, const unsigned int a_height)
{
    internalResize(a_width, a_height);
}