#include "pch.h"
#include "VulkanShader.h"
#include <fstream>


VulkanShader::VulkanShader(const VulkanDeviceContext& a_ctxt) : VulkanObject{ a_ctxt }
{
	// todo
}

VulkanShader::~VulkanShader()
{
	cleanup();
	// todo
}

void VulkanShader::cleanup()
{
	// release shader modules
	for (const auto& shaderInfo : m_shaderStageCreateInfo)
		vkDestroyShaderModule(m_ctxt.logicalDevice, shaderInfo.module, nullptr);
}

void VulkanShader::loadShaderSpirV(const std::string& a_filename, const VkShaderStageFlagBits a_stage)
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

void VulkanShader::createDescriptorUniformTexelBufferBindings(const VkShaderStageFlagBits a_shaderFlag, const uint32_t a_bind, const uint32_t _descriptorCount)
{
    //
}

void VulkanShader::createDescriptorStorageTexelBufferBindings(const VkShaderStageFlagBits a_shaderFlag, const uint32_t a_bind, const uint32_t _descriptorCount)
{
    //
}

void VulkanShader::createDescriptorUniformBufferBindings(const VkShaderStageFlagBits a_shaderFlag, const uint32_t a_bind, const uint32_t _descriptorCount)
{
    //
}

void VulkanShader::createDescriptorStorageBufferBindings(const VkShaderStageFlagBits a_shaderFlag, const uint32_t a_bind, const uint32_t _descriptorCount)
{
    //
}

void VulkanShader::createDescriptorUniformBufferDynBindings(const VkShaderStageFlagBits a_shaderFlag, const uint32_t a_bind, const uint32_t _descriptorCount)
{
    //
}

void VulkanShader::createDescriptorStorageBufferDynBindings(const VkShaderStageFlagBits a_shaderFlag, const uint32_t a_bind, const uint32_t _descriptorCount)
{
    //
}

void VulkanShader::createDescriptorSampledImageBindings(const VkShaderStageFlagBits a_shaderFlag, const uint32_t a_bind, const uint32_t _descriptorCount)
{
    //
}

void VulkanShader::createDescriptorStorageImageBindings(const VkShaderStageFlagBits a_shaderFlag, const uint32_t a_bind, const uint32_t _descriptorCount)
{
    //
}

void VulkanShader::createDescriptorLayouts()
{
    //
}