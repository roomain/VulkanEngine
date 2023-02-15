#pragma once
#include <memory>
#include <vulkan/vulkan.h>
#include "vk_globals.h"
#include "vk_object.h"

namespace Vulkan
{
	class VK_Shader;

	/*@brief base class for pipline*/
	class ENGINE_EXPORT VK_Pipeline : public VK_Object
	{
	private:
		VkPipeline m_vkPipline;					/*!< vulkan pipline handle*/
		VkPipelineLayout m_vkpipelineLayout;	/*!< vulkan pipline layout handle*/
		std::shared_ptr<VK_Shader> m_pShader;	/*!< shared shader*/
		int m_priority;							/*!< pipline priority*/

	public:
		explicit [[nodiscard]] VK_Pipeline(std::shared_ptr<VK_Device>& a_pDevice, const int a_priority, std::shared_ptr<VK_Shader>& a_pShader);
		virtual ~VK_Pipeline();
		/*@brief get pipeline priority*/
		[[nodiscard]] constexpr int priority()const noexcept { return m_priority; }
		/*@brief check validity*/
		[[nodiscard]] bool isValid()const noexcept;
		/*@brief create commands*/
		virtual void createCommands(/*TODO*/) = 0;
		/*@brief destoy pipeline*/
		virtual void destroy();
	};

	using VK_PipelinePtr = std::shared_ptr<VK_Pipeline>;
}