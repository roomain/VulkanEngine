#include "pch.h"
#include "VulkanPipeline.h"
#include <fstream>


VulkanPipeline::VulkanPipeline(const VulkanDeviceContext& a_ctxt) : VulkanObject<VulkanDeviceContext>{ a_ctxt }
{
	// todo
}

VulkanPipeline::~VulkanPipeline()
{
	cleanup();
}

void VulkanPipeline::loadShaderSpirV(const std::string& a_filename, const VkShaderStageFlagBits a_stage)
{
	if (std::ifstream fileStream(a_filename, std::ios::binary | std::ios::in | std::ios::ate); fileStream.is_open())
	{
		const size_t fileSize = fileStream.tellg();
		fileStream.seekg(0, std::ios::beg);

		if (fileSize > 0)
		{
			std::vector<char> fileData(fileSize);
			fileStream.read(fileData.data(), fileSize);
			fileStream.close();

			// Create a new shader module that will be used for pipeline creation
			VkShaderModuleCreateInfo shaderModuleCI = Vulkan::Initializers::shaderModuleCreateInfo(fileData);
			VkShaderModule shaderModule = VK_NULL_HANDLE;
			VK_CHECK_EXCEPT(vkCreateShaderModule(m_ctxt.logicalDevice, &shaderModuleCI, nullptr, &shaderModule))
			m_shaderStageCreateInfo.emplace_back(Vulkan::Initializers::pipelineShaderStageCreateInfo(a_stage, shaderModule));
		}

	}
}

void VulkanPipeline::cleanup()
{
	if(m_pipeline != VK_NULL_HANDLE)
		vkDestroyPipeline(m_ctxt.logicalDevice, m_pipeline, nullptr);

	// release shader modules
	for(const auto& shaderInfo : m_shaderStageCreateInfo)
		vkDestroyShaderModule(m_ctxt.logicalDevice, shaderInfo.module, nullptr);
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

void VulkanPipeline::setupRenderPass()
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
	VK_CHECK_EXCEPT(vkCreateRenderPass(m_ctxt.logicalDevice, &renderPassCI, nullptr, &renderPass))
}

void VulkanPipeline::create()
{
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