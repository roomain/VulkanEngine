#pragma once
#include <memory>

namespace Vulkan
{
	/*@brief base class for shader*/
	class VK_Shader
	{
	private:
		//

	public:
		[[nodiscard]] VK_Shader();
		virtual ~VK_Shader();
	};

	using VK_ShaderPtr = std::shared_ptr< VK_Shader>;
}

