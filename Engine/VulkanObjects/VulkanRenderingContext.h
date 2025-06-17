#pragma once
/***********************************************
* @headerfile VulkanRenderingContext.h
* @date 21 / 04 / 2025
* @author Roomain
************************************************/
#include "glm/glm.hpp"
#pragma warning(push)
#pragma warning( disable : 4201 )
#include "glm/gtx/quaternion.hpp"
#pragma warning(pop)

/*@brief represent a viewport*/
struct VulkanViewport
{
    unsigned int m_posX;
    unsigned int m_posY;
    unsigned int m_width;
    unsigned int m_height;
};

/*@brieaf represents the camer*/
struct VulkanCamera
{
    glm::dvec3 m_position;
    glm::dquat m_orientation;
    glm::dmat4 m_projection;
};

/*@brief the current context*/
struct VulkanRenderingContext
{
    VulkanViewport m_currentViewport;
    VulkanCamera m_currentCamera;
};