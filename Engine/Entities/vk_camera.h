#pragma once
#include <memory>
#include "vk_movable.h"
#include "entities_globals.h"

namespace Vulkan
{
	class ENTITIES_EXPORT VK_Camera : public VK_Movable
	{
	private:
		glm::mat4 m_projection;	/*!< projection matrix*/
		
	public:
		[[nodiscard]] VK_Camera();
		virtual ~VK_Camera();
		/*@brief ortho projection*/
		VK_Camera& setOrthoProjection(const float a_left, const float a_right, const float a_bottom, const float a_top);
		VK_Camera& setOrthoProjection(const float a_left, const float a_right, const float a_bottom, const float a_top, const float a_near, const float a_far);

		/*@brief perspective projection*/
		VK_Camera& setPerspectiveProjection(const float a_fovY, const float a_ratio, const float a_near, const float a_far);

		/*@return camera projection matrix*/
		[[nodiscard]] constexpr const glm::mat4& projection()const { return m_projection; }
	};

	using VK_CameraPtr = std::shared_ptr<VK_Camera>;
}
