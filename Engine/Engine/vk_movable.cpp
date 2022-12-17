#include "pch.h"
#include "vk_movable.h"
#include <glm/ext/matrix_transform.hpp>

namespace Vulkan
{

	VK_Movable::VK_Movable() : m_transformation{ glm::identity<glm::mat4>() }
	{
	}

	VK_Movable::~VK_Movable()
	{
		//
	}

	VK_Movable& VK_Movable::translate(const glm::vec3& a_trans)
	{
		// optimization
		m_transformation[3] += glm::vec4(a_trans, 0.0f);
		return *this;
	}

	VK_Movable& VK_Movable::rotate(const float a_radian, const glm::vec3& a_axis)
	{
		glm::vec4 vecTranslation = m_transformation[3];
		vecTranslation.w = 0;
		m_transformation[3] -= vecTranslation;
		m_transformation = glm::rotate(m_transformation, a_radian, a_axis);
		m_transformation[3] += vecTranslation;
		return *this;
	}

	VK_Movable& VK_Movable::rotate(const float a_radian, const glm::vec3& a_axis, const glm::vec3& a_axisOrigin)
	{
		m_transformation[3] -= glm::vec4(a_axisOrigin, 0.0f);
		m_transformation = glm::rotate(m_transformation, a_radian, a_axis);
		m_transformation[3] += glm::vec4(a_axisOrigin, 0.0f);
		return *this;
	}

}