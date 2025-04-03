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