#pragma once
#include <memory>
#include <vulkan/vulkan.h>
#include "vk_globals.h"

namespace Vulkan
{
	/*@brief base class for pipline*/
	class ENGINE_EXPORT VK_Pipeline
	{
	private:
		VkPipeline m_vkPipline;					/*!< vulkan pipline handle*/
		VkPipelineLayout m_vkpipelineLayout;	/*!< vulkan pipline layout handle*/

		int m_priority;							/*!< pipline priority*/
		

	public:
		VK_Pipeline(const int a_priority);
		virtual ~VK_Pipeline();
		//
		/*@brief get pipeline priority*/
		[[nodiscard]] constexpr int priority()const noexcept { return m_priority; }
		/*@brief check validity*/
		[[nodiscard]] bool isValid()const noexcept;
		/*@brief create commands*/
		virtual void createCommands(/*TODO*/) = 0;
		/*@brief destoy pipeline*/
		virtual void destroy(VkDevice a_device);
	};

	using VK_PipelinePtr = std::shared_ptr<VK_Pipeline>;
}