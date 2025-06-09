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
	std::vector<VkSubpassDependency> subpassesDepends;

	int curIndex = 0;
	for (const VkAttachmentDescription& attachment : m_attachement)
	{
		VkSubpassDependency depends;
		depends.srcSubpass = VK_SUBPASS_EXTERNAL;
		depends.dstSubpass = 0;
		depends.dependencyFlags = 0;
		VkAttachmentReference ref{ .attachment = 0 };
		if (curIndex == m_depthAttachmentIndex)
		{
			depends.srcStageMask = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
			depends.dstStageMask = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
			depends.srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
			depends.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;

			ref.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
		}
		else
		{
			depends.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			depends.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			depends.srcAccessMask = 0;
			depends.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_COLOR_ATTACHMENT_READ_BIT;
			
			ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		}
		subpassesDepends.emplace_back(depends);
		subpassesDepends.emplace_back(ref);
		++curIndex;
	}

	VkRenderPassCreateInfo renderPassCI = Vulkan::Initializers::createRenderPass(0, m_attachement, subpass, subpassesDepends);
	VK_CHECK_EXCEPT(vkCreateRenderPass(m_ctxt.logicalDevice, &renderPassCI, nullptr, &a_renderPass))
}
