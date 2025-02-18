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
	Transformation() : m_transformMatrix{glm::identity<glm::dmat4>()}{}
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
		m_transformMatrix = glm::translate(m_transformMatrix, -a_center);
		m_transformMatrix = glm::rotate(m_transformMatrix, a_radianAngle, a_axis);
		m_transformMatrix = glm::translate(m_transformMatrix, a_center);
	}

	inline void reset()
	{
		m_transformMatrix = glm::identity<glm::dmat4>();
	}

	/*@brief self rotate*/
	inline void selfRotate(const glm::dvec3& a_axis, const double& a_radianAngle)
	{
		rotateAround(getPosition(), a_axis, a_radianAngle);
	}

	/*@brief set position*/
	inline void setPosition(const glm::dvec3& a_position)
	{
		m_transformMatrix[3] = glm::dvec4(a_position, 1);
	}

	/*@brief translate*/
	inline void translate(const glm::dvec3& a_translation)
	{
		m_transformMatrix = glm::translate(m_transformMatrix, a_translation);
	}

	inline void scale(const glm::dvec3& a_scale)
	{
		m_transformMatrix = glm::scale(m_transformMatrix, a_scale);
	}

	inline void setScale(const glm::dvec3& a_scale)
	{
		m_transformMatrix[0][0] = a_scale.x;
		m_transformMatrix[1][1] = a_scale.y;
		m_transformMatrix[2][2] = a_scale.z;
	}

	constexpr glm::dvec3 getPosition()const
	{
		return m_transformMatrix[3];
	}

	constexpr glm::dvec3 getScale()const
	{
		return glm::dvec3(m_transformMatrix[0][0], m_transformMatrix[1][1], m_transformMatrix[2][2]);
	}

	constexpr glm::dquat getOrientation()const
	{
		return glm::quat_cast(m_transformMatrix);
	}
};
