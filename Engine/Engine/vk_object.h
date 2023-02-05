#pragma once
#include <memory>

namespace Vulkan
{
	class VK_Device;

	/*@brief base vulkan object*/
	class VK_Object
	{
	protected:
		std::weak_ptr<VK_Device> m_vkDevice; /*!< associated vulkan device*/

	public:
		VK_Object() = delete;
		explicit [[nodiscard]] VK_Object(std::shared_ptr<VK_Device>& a_pDevice) : m_vkDevice{ a_pDevice } {}
		virtual ~VK_Object() = default;
	};
}