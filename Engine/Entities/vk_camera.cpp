#include "pch.h"
#include "vk_camera.h"
#include <glm/ext.hpp>

namespace Vulkan
{
	VK_Camera::VK_Camera() : VK_Movable{}, m_projection{ glm::ortho(-1, 1, -1, 1) }
	{
		//
	}

	VK_Camera::~VK_Camera()
	{
		//
	}

	VK_Camera& VK_Camera::setOrthoProjection(const float a_left, const float a_right, const float a_bottom, const float a_top)
	{
		m_projection = glm::ortho(a_left, a_right, a_bottom, a_top);
		return *this;
	}

	VK_Camera& VK_Camera::setOrthoProjection(const float a_left, const float a_right, const float a_bottom, const float a_top, const float a_near, const float a_far)
	{
		m_projection = glm::ortho(a_left, a_right, a_bottom, a_top, a_near, a_far);
		return *this;
	}

	VK_Camera& VK_Camera::setPerspectiveProjection(const float a_fovY, const float a_ratio, const float a_near, const float a_far)
	{
		m_projection = glm::perspective(a_fovY, a_ratio, a_near, a_far);
		return *this;
	}

}