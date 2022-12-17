#include "pch.h"
#include "vk_module.h"

namespace Vulkan
{
	VK_Module::VK_Module(std::shared_ptr<VK_Renderer>& a_pRenderer) : m_pRenderer{ a_pRenderer }
	{
		//
	}

	VK_Module::~VK_Module()
	{
		//
	}
}