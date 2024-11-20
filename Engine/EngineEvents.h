#pragma once
/***********************************************
* @headerfile EngineEvents.h
* @date 31 / 10 / 2024
* @author Roomain
************************************************/
#include "glm/glm.hpp"
#include "common/bitOperators.h"

enum class EngineEventType
{
	MouseEvent_Enter,
	MouseEvent_Leave,
	MouseEvent_ButtonPressed,
	MouseEvent_ButtonReleased,
	MouseEvent_Click,
	MouseEvent_DoubleClick,
	MouseEvent_Move
};


enum class EngineMouseEventButtonFlag
{
	NoButton = 0,
	LeftButton,
	MiddleButton,
	RightButton
};

struct EngineMouseEvent
{
	EngineEventType type;				/*!< specific event type*/
	float positionX;					/*!< mouse position X*/
	float positionY;					/*!< mouse position Y*/
	float directionX;					/*!< relative direction X*/
	float directionY;					/*!< relative direction Y*/
	float deltaWheel;                   /*!< mouse wheel*/
	EngineMouseEventButtonFlag buttons; /*!< button flag pressed*/
	glm::vec3 worldPosition;            /*!< mouse world position*/
};

struct EngineResizeEvent
{
	uint32_t oldWidth;      /*!< old window width*/
	uint32_t oldHeight;     /*!< old window height*/
	uint32_t newWidth;      /*!< new window width*/
	uint32_t newHeight;     /*!< new window height*/
};

struct EngineCloseEvent
{
	// todo
};