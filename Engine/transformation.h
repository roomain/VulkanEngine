#pragma once
/***********************************************
* @headerfile transformation.h
* @date 25 / 01 / 2025
* @author Roomain
************************************************/
#include <glm/glm.hpp>
#include <glm/ext.hpp>

/*@brief represents a 3D transformation*/
class Transformation
{
private:
	glm::dmat4 m_transformMatrix;

public:
	explicit Transformation(const glm::dmat4& a_transform) : m_transformMatrix{ a_transform } {}
	explicit Transformation(const glm::dmat4&& a_transform)noexcept : m_transformMatrix{ a_transform } {}
	inline const glm::dmat4& matrix()const { return m_transformMatrix; }
	inline explicit operator const glm::dmat4& () const { return m_transformMatrix; }

	inline Transformation operator * (const Transformation& a_other)const
	{
		return Transformation(m_transformMatrix * a_other.m_transformMatrix);
	}

	inline void operator *= (const Transformation& a_other)
	{
		m_transformMatrix = m_transformMatrix * a_other.m_transformMatrix;
	}

	/*@brief rotate around a point with axis*/
	inline void rotateAround(const glm::dvec3& a_center, const glm::dvec3& a_axis, const double& a_radianAngle)
	{
		//glm::rotate()
		// todo
	}

	/*@brief self rotate*/
	inline void selfRotate(const glm::dvec3& a_axis, const double& a_radianAngle)
	{
		//todo
	}

	/*@brief set position*/
	inline void setPosition(const glm::dvec3& a_position)
	{
		//todo
	}

	/*@brief translate*/
	inline void translate(const glm::dvec3& a_translation)
	{
		//todo
	}
};