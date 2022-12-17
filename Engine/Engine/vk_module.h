#pragma once
#include <memory>

namespace Vulkan
{
	class VK_Renderer;

	/*@brief module for vulkan engine*/
	class VK_Module
	{
	public:
		[[nodiscard]] VK_Module(std::shared_ptr<VK_Renderer>& a_pRenderer);
		virtual ~VK_Module();

	private:
		std::shared_ptr<VK_Renderer> m_pRenderer;	/*!< shared pointer on vulkan renderer*/
	};
}

