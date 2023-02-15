#pragma once
#include <memory>
#include "vk_object.h"

namespace Vulkan
{
	/*@brief base class for shader*/
	class VK_Shader : public VK_Object
	{
	private:
		//

	public:
		VK_Shader() = delete;
		explicit [[nodiscard]] VK_Shader(std::shared_ptr<VK_Device>& a_pDevice);
		virtual ~VK_Shader();
	};

	using VK_ShaderPtr = std::shared_ptr< VK_Shader>;
}

