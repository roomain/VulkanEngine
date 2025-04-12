#pragma once
/***********************************************
* @headerfile transformation.h
* @date 25 / 01 / 2025
* @author Roomain
************************************************/
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace glmEx
{
	//@brief create rotation matrix around axis and point
	inline glm::dmat4 rotateAround(const glm::dvec3& a_center, const glm::dvec3& a_axis, const double& a_radianAngle)
	{
		glm::dmat4 matRet;
		matRet = glm::translate(matRet, -a_center);
		matRet = glm::rotate(matRet, a_radianAngle, a_axis);
		return glm::translate(matRet, a_center);
	}

	// set position to matrix
	inline void setPosition(glm::dmat4& a_mat, const glm::dvec3& a_position)
	{
		a_mat[3] = glm::dvec4(a_position, 1);
	}

	// get position from matrix
	inline glm::dvec3 getPosition(const glm::dmat4& a_mat)
	{
		return a_mat[3];
	}

	inline glm::dvec3 getScale(const glm::dmat4& a_mat)
	{
		return  glm::dvec3(a_mat[0][0], a_mat[1][1], a_mat[2][2]);
	}

}