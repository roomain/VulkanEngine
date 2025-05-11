#include "pch.h"
#include "VulkanPipeline.h"
#include "VulkanShader.h"

VulkanPipeline::VulkanPipeline(const VulkanDeviceContext& a_ctxt) : VulkanObject<VulkanDeviceContext>{ a_ctxt }
{
	// todo
}

VulkanPipeline::~VulkanPipeline()
{
	cleanup();
}

void VulkanPipeline::setShader(const std::shared_ptr<VulkanShader>& a_shader)
{
	m_shader = a_shader;
}

void VulkanPipeline::cleanup()
{
	if (m_pipeline != VK_NULL_HANDLE)
		vkDestroyPipeline(m_ctxt.logicalDevice, m_pipeline, nullptr);
	m_pipeline = VK_NULL_HANDLE;

	if(m_pipelineLayout != VK_NULL_HANDLE)
		vkDestroyPipelineLayout(m_ctxt.logicalDevice, m_pipelineLayout, nullptr);
	m_pipelineLayout = VK_NULL_HANDLE;

	if (m_descriptorSetLayout != VK_NULL_HANDLE)
		vkDestroyDescriptorSetLayout(m_ctxt.logicalDevice, m_descriptorSetLayout, nullptr);
	m_descriptorSetLayout = VK_NULL_HANDLE;
}

void VulkanPipeline::addAttachment(const VkAttachmentDescription& a_attachement)
{
	m_attachement.emplace_back(a_attachement);
}

void VulkanPipeline::setDepthAttachment(const VkAttachmentDescription& a_attachement)
{
	m_depthAttachmentIndex = static_cast<int>(m_attachement.size());
	m_attachement.emplace_back(a_attachement);
}

void VulkanPipeline::setupRenderPass(VkRenderPass& a_renderPass)
{
	std::vector<VkSubpassDescription> subpass;
	std::vector<VkSubpassDependency> subpassesDepends;

	int curIndex = 0;
	for (const VkAttachmentDescription& attachment : m_attachement)
	{
		VkSubpassDependency depends;
		VkAttachmentReference ref{ .attachment = 0 };
		if (curIndex == m_depthAttachmentIndex)
		{
			depends.srcSubpass = VK_SUBPASS_EXTERNAL;
			depends.dstSubpass = 0;
			depends.srcStageMask = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
			depends.dstStageMask = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
			depends.srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
			depends.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;
			depends.dependencyFlags = 0;

			ref.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
		}
		else
		{
			depends.srcSubpass = VK_SUBPASS_EXTERNAL;
			depends.dstSubpass = 0;
			depends.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			depends.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			depends.srcAccessMask = 0;
			depends.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_COLOR_ATTACHMENT_READ_BIT;
			depends.dependencyFlags = 0;
			
			ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		}
		subpassesDepends.emplace_back(depends);
		subpassesDepends.emplace_back(ref);
		++curIndex;
	}

	VkRenderPassCreateInfo renderPassCI = Vulkan::Initializers::createRenderPass(0, m_attachement, subpass, subpassesDepends);
	VK_CHECK_EXCEPT(vkCreateRenderPass(m_ctxt.logicalDevice, &renderPassCI, nullptr, &a_renderPass))
}

bool VulkanPipeline::create(const VkPipelineVertexInputStateCreateInfo& a_vertexInput, const VkPipelineInputAssemblyStateCreateInfo& a_inputAssemblyState)
{
	if (m_shader)
	{
		VkRenderPass renderPass;
		setupRenderPass(renderPass);
		VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCI = Vulkan::Initializers::descriptorSetLayoutCreateInfo(
			m_shader->m_layoutBindings.data(), static_cast<uint32_t>(m_shader->m_layoutBindings.size()));
		VK_CHECK_EXCEPT(vkCreateDescriptorSetLayout(m_ctxt.logicalDevice, &descriptorSetLayoutCI, nullptr,
			&m_descriptorSetLayout));

		VkPipelineLayoutCreateInfo pipelineLayoutCi = Vulkan::Initializers::pipelineLayoutCreateInfo(m_descriptorSetLayout);
		VK_CHECK_EXCEPT(vkCreatePipelineLayout(m_ctxt.logicalDevice, &pipelineLayoutCi, nullptr, &m_pipelineLayout));

		VkPipelineTessellationStateCreateInfo tessellationState;
		VkPipelineViewportStateCreateInfo viewportState;
		VkPipelineRasterizationStateCreateInfo rasterizationState;
		VkPipelineMultisampleStateCreateInfo multisampleState;
		VkPipelineDepthStencilStateCreateInfo depthStencilState;
		VkPipelineColorBlendStateCreateInfo colorBlendState;
		VkPipelineDynamicStateCreateInfo dynamicState;

		VkGraphicsPipelineCreateInfo pipelineCI = Vulkan::Initializers::createGraphicPipeline(
			0,
			m_shader->m_shaderStageCreateInfo,
			&a_vertexInput,
			&a_inputAssemblyState,
			&tessellationState,
			&viewportState,
			&rasterizationState,
			&multisampleState,
			&depthStencilState,
			&colorBlendState,
			&dynamicState,
			m_pipelineLayout,
			renderPass,
			uint32_t         a_subpass,
			VkPipeline       a_basePipelineHandle = VK_NULL_HANDLE,
			int32_t          a_basePipelineIndex = -1
		);
		
		return true;
	}
	return false;
}