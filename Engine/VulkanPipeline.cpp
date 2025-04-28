#include "pch.h"
#include "VulkanPipeline.h"


VulkanPipeline::VulkanPipeline(const VulkanDeviceContext& a_ctxt) : VulkanObject<VulkanDeviceContext>{ a_ctxt }
{
	// todo
}

VulkanPipeline::~VulkanPipeline()
{
	cleanup();
}


void VulkanPipeline::cleanup()
{
	if(m_pipeline != VK_NULL_HANDLE)
		vkDestroyPipeline(m_ctxt.logicalDevice, m_pipeline, nullptr);

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

void VulkanPipeline::create()
{
	VkRenderPass renderPass;
	setupRenderPass(renderPass);
	VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCI = Vulkan::Initializers::descriptorSetLayoutCreateInfo();

	VkPipelineLayoutCreateInfo pipelinLayoutCi = Vulkan::Initializers::pipelineLayoutCreateInfo();

	VkGraphicsPipelineCreateInfo pipelineCI = Vulkan::Initializers::createGraphicPipeline(
		const VkPipelineCreateFlags a_flags,
		const std::vector<VkPipelineShaderStageCreateInfo>&a_shaderStages,
		const VkPipelineVertexInputStateCreateInfo * a_pVertexInputState,
		const VkPipelineInputAssemblyStateCreateInfo * a_pInputAssemblyState,
		const VkPipelineTessellationStateCreateInfo * a_pTessellationState,
		const VkPipelineViewportStateCreateInfo * a_pViewportState,
		const VkPipelineRasterizationStateCreateInfo * a_pRasterizationState,
		const VkPipelineMultisampleStateCreateInfo * a_pMultisampleState,
		const VkPipelineDepthStencilStateCreateInfo * a_pDepthStencilState,
		const VkPipelineColorBlendStateCreateInfo * a_pColorBlendState,
		const VkPipelineDynamicStateCreateInfo * a_pDynamicState,
		VkPipelineLayout a_layout,
		renderPass,
		uint32_t         a_subpass,
		VkPipeline       a_basePipelineHandle = VK_NULL_HANDLE,
		int32_t          a_basePipelineIndex = -1
	);
	//
	//VkGraphicsPipelineCreateInfo pipelineLibraryCI = Vulkan::Initializers::graphicPipelineCreateInfo(
	//	VK_PIPELINE_CREATE_LIBRARY_BIT_KHR | VK_PIPELINE_CREATE_RETAIN_LINK_TIME_OPTIMIZATION_INFO_BIT_EXT,
	//	m_shaderStageCreateInfo,
	//);
	//pipelineLibraryCI.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	//pipelineLibraryCI.pNext = &libraryInfo;
	//pipelineLibraryCI.renderPass = renderPass;
	//pipelineLibraryCI.flags = VK_PIPELINE_CREATE_LIBRARY_BIT_KHR | VK_PIPELINE_CREATE_RETAIN_LINK_TIME_OPTIMIZATION_INFO_BIT_EXT;
	//pipelineLibraryCI.stageCount = static_cast<uint32_t>(m_shaderStageCreateInfo.size());
	//pipelineLibraryCI.pStages = m_shaderStageCreateInfo.data();
	//pipelineLibraryCI.layout = pipelineLayout;
	//pipelineLibraryCI.pDynamicState = &dynamicInfo;
	//pipelineLibraryCI.pViewportState = &viewportState;
	//pipelineLibraryCI.pRasterizationState = &rasterizationState;
	//VK_CHECK_RESULT(vkCreateGraphicsPipelines(m_ctxt.logicalDevice, m_pipeline, 1, &pipelineLibraryCI, nullptr, &pipelineLibrary.preRasterizationShaders));
}