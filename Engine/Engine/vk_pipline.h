#pragma once
#include <vulkan/vulkan.h>
#include "vk_globals.h"

namespace Vulkan
{
	/*@brief base class for pipline*/
	class ENGINE_EXPORT VK_Pipline
	{
	private:
		VkPipeline m_vkPipline;					/*!< vulkan pipline handle*/
		VkPipelineLayout m_vkpipelineLayout;	/*!< vulkan pipline layout handle*/
		

	public:
		//
		bool isValid()const noexcept;
	};
}