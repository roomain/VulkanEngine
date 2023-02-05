#pragma once
#include <memory>
#include "vk_object.h"

namespace Vulkan
{
	/*@brief module for vulkan engine*/
	class VK_Module : public VK_Object
	{
	public:
		explicit [[nodiscard]] VK_Module(std::shared_ptr<VK_Device>& a_pDevice);
		virtual ~VK_Module();

	};
}

