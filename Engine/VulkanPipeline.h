#pragma once
/***********************************************
* @headerfile VulkanPipeline.h
* @date 25 / 02 / 2025
* @author Roomain
************************************************/
#include <vector>
#include <vulkan/vulkan.hpp>
#include "VulkanObject.h"
#include "common/notCopiable.h"
#include "VulkanLocalsContexts.h"

class VulkanShader;

/*@brief represents a vulkan pipeline*/
class VulkanPipeline : public VulkanObject<VulkanDeviceContext>
{
private:
	int m_depthAttachmentIndex = -1;										/*!< index of depth attachment in m_attachment*/
	std::vector<VkAttachmentDescription> m_attachement;						/*!< list of attachment*/
	std::vector<VkPipelineShaderStageCreateInfo> m_shaderStageCreateInfo;
	VkPipeline m_pipeline = VK_NULL_HANDLE;
	std::shared_ptr<VulkanShader> m_shader;
	VkDescriptorSetLayout m_descriptorSetLayout = VK_NULL_HANDLE;
	VkPipelineLayout m_pipelineLayout = VK_NULL_HANDLE;
	// todo shaders modules
	//

protected:
	virtual void setupRenderPass(VkRenderPass& a_renderPass);

public:
	template<typename VertexType>
	static void setupPipeline(/*todo*/)
	{
		VertexInputBindingDescVector vertexInput =
		{
			{
				.binding = 1,
				.stride = sizeof(VertexType),
				.inputRate = VkVertexInputRate::VK_VERTEX_INPUT_RATE_VERTEX,
			}
		};

		VertexType vertexInstance;
		VertexInputAttribDescVector vertexAttributes = inputDescription(vertexInstance);

		VkPipelineVertexInputStateCreateInfo vertexInput = Vulkan::Initializers::pipelineVertexInputStateCreateInfo(
			vertexInput, vertexAttributes
		);
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyState;
	}


	NOT_COPIABLE(VulkanPipeline)
	explicit VulkanPipeline(const VulkanDeviceContext& a_ctxt);
	virtual ~VulkanPipeline();
	inline std::shared_ptr<VulkanShader> shader()const { return m_shader; }
	void setShader(const std::shared_ptr<VulkanShader>& a_shader);

	void cleanup();
	virtual bool create(const VkPipelineVertexInputStateCreateInfo& a_vertexInput, const VkPipelineInputAssemblyStateCreateInfo& a_inputAssemblyState);

	void addAttachment(const VkAttachmentDescription& a_attachement);
	void setDepthAttachment(const VkAttachmentDescription& a_attachement);

	// todo
};
