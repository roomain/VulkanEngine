#pragma once
#include <glm/glm.hpp>
#include "vk_globals.h"

namespace Vulkan
{
	/*@brief base class for movable objects*/
	class ENGINE_EXPORT VK_Movable
	{
	protected:
		glm::mat4 m_transformation; /*!< transformation matrix*/

	public:
		VK_Movable();
		virtual ~VK_Movable();
		[[nodiscard]] constexpr glm::mat4 transformation()const { return m_transformation; }
		/*@brief translate the object*/
		virtual VK_Movable& translate(const glm::vec3& a_trans);
		/*rotate object on axis*/
		virtual VK_Movable& rotate(const float a_radian, const glm::vec3& a_axis);
		/*rotate object around an axis*/
		virtual VK_Movable& rotate(const float a_radian, const glm::vec3& a_axis, const glm::vec3& a_axisOrigin);
	};
}

