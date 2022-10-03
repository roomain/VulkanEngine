#pragma once
#include <vulkan/vulkan.h>

namespace Vulkan
{
	class VK_Pipline
	{
	private:
		VkPipeline m_vkPipline;					/*!< vulkan pipline handle*/
		VkPipelineLayout m_vkpipelineLayout;	/*!< vulkan pipline layout handle*/
		//

	public:
		//
		bool isValid()const noexcept;
	};
}