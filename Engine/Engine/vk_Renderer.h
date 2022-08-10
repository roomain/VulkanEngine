#pragma once
#include "vk_ext_struct.h"

namespace Vulkan
{
	/*@brief vulkan renderer*/
	class VK_Renderer
	{
	public:


		// LOADING FUNCTIONS
		/*@brief load a shader*/

	private:
		Device m_device;

		static VK_Renderer* m_pInstance;

		VK_Renderer();
	};
}

