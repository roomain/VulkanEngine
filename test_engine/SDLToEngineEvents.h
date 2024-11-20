#pragma once
#include "EngineEvents.h"
#include "SDL3/SDL.h"

constexpr [[no_discard]] EngineMouseEventButtonFlag toEngine(const SDL_MouseButtonFlags a_button)
{
	EngineMouseEventButtonFlag flagRet = EngineMouseEventButtonFlag::NoButton;
	if ((a_button & SDL_BUTTON_LEFT) == SDL_BUTTON_LEFT)
		flagRet = flagRet | EngineMouseEventButtonFlag::LeftButton;


	if ((a_button & SDL_BUTTON_MIDDLE) == SDL_BUTTON_MIDDLE)
		flagRet = flagRet | EngineMouseEventButtonFlag::MiddleButton;


	if ((a_button & SDL_BUTTON_RIGHT) == SDL_BUTTON_RIGHT)
		flagRet = flagRet | EngineMouseEventButtonFlag::RightButton;

	return flagRet;
}

constexpr [[no_discard]] EngineMouseEvent toEngineEvent(const SDL_MouseMotionEvent& a_event)
{
	return EngineMouseEvent{
		.type = EngineEventType::MouseEvent_Move,
		.positionX = a_event.x,
		.positionY = a_event.y,
		.directionX = a_event.xrel,
		.directionY = a_event.yrel,
		.deltaWheel = 0,
		.buttons = toEngine(a_event.state) 
	};
}

constexpr [[no_discard]] EngineMouseEvent toEngineEvent(const SDL_MouseButtonEvent& a_event)
{
	return EngineMouseEvent{};
}

constexpr [[no_discard]] EngineMouseEvent toEngineEvent(const SDL_MouseWheelEvent& a_event)
{
	return EngineMouseEvent{};
}