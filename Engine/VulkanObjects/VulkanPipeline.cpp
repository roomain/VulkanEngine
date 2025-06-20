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

void VulkanPipeline::bind(VkCommandBuffer& a_cmdBuffer)const
{
	vkCmdBindPipeline(a_cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeline);
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
	std::vector<VkSubpassDependency> subpassesDepends;

	std::vector<VkAttachmentReference> colorAttach;
	VkAttachmentReference depthRef;
	for(int index = 0; index < m_attachement.size(); ++index)
	{
		VkSubpassDependency depends;
		depends.srcSubpass = VK_SUBPASS_EXTERNAL;
		depends.dstSubpass = 0;
		depends.dependencyFlags = 0;
		if (index == m_depthAttachmentIndex)
		{
			depends.srcStageMask = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
			depends.dstStageMask = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
			depends.srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
			depends.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;

			depthRef.attachment = m_depthAttachmentIndex;
			depthRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
		}
		else
		{
			depends.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			depends.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			depends.srcAccessMask = 0;
			depends.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_COLOR_ATTACHMENT_READ_BIT;

			colorAttach.emplace_back(VkAttachmentReference{ .attachment = static_cast<uint32_t>(index),
				.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL });
		}
		subpassesDepends.emplace_back(depends);
	}
		
	VkSubpassDescription subpassDescription = Vulkan::Initializers::createGraphicSubpassDesc(colorAttach, m_depthAttachmentIndex >= 0 ? &depthRef : nullptr);
	
	VkRenderPassCreateInfo renderPassCI = Vulkan::Initializers::createRenderPass(0, m_attachement, subpassDescription, subpassesDepends);
	VK_CHECK_EXCEPT(vkCreateRenderPass(m_ctxt.logicalDevice, &renderPassCI, nullptr, &a_renderPass))
}
