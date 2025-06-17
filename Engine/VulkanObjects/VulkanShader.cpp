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

void VulkanShader::createDescriptorUniformTexelBufferBindings(const VkShaderStageFlags a_shaderFlag, const uint32_t a_bind, const uint32_t _descriptorCount)
{
	m_layoutBindings.emplace_back(VkDescriptorSetLayoutBinding{
		.binding = a_bind,
		.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER,
		.descriptorCount = _descriptorCount,
		.stageFlags = a_shaderFlag,
		.pImmutableSamplers = nullptr
	});
}

void VulkanShader::createDescriptorStorageTexelBufferBindings(const VkShaderStageFlags a_shaderFlag, const uint32_t a_bind, const uint32_t _descriptorCount)
{
	m_layoutBindings.emplace_back(VkDescriptorSetLayoutBinding{
		.binding = a_bind,
		.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER,
		.descriptorCount = _descriptorCount,
		.stageFlags = a_shaderFlag,
		.pImmutableSamplers = nullptr
	});
}

void VulkanShader::createDescriptorUniformBufferBindings(const VkShaderStageFlags a_shaderFlag, const uint32_t a_bind, const uint32_t _descriptorCount)
{
	m_layoutBindings.emplace_back(VkDescriptorSetLayoutBinding{
		.binding = a_bind,
		.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
		.descriptorCount = _descriptorCount,
		.stageFlags = a_shaderFlag,
		.pImmutableSamplers = nullptr
	});
}

void VulkanShader::createDescriptorStorageBufferBindings(const VkShaderStageFlags a_shaderFlag, const uint32_t a_bind, const uint32_t _descriptorCount)
{
	m_layoutBindings.emplace_back(VkDescriptorSetLayoutBinding{
		.binding = a_bind,
		.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
		.descriptorCount = _descriptorCount,
		.stageFlags = a_shaderFlag,
		.pImmutableSamplers = nullptr
	});
}

void VulkanShader::createDescriptorUniformBufferDynBindings(const VkShaderStageFlags a_shaderFlag, const uint32_t a_bind, const uint32_t _descriptorCount)
{
	m_layoutBindings.emplace_back(VkDescriptorSetLayoutBinding{
		.binding = a_bind,
		.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC,
		.descriptorCount = _descriptorCount,
		.stageFlags = a_shaderFlag,
		.pImmutableSamplers = nullptr
	});
}

void VulkanShader::createDescriptorStorageBufferDynBindings(const VkShaderStageFlags a_shaderFlag, const uint32_t a_bind, const uint32_t _descriptorCount)
{
	m_layoutBindings.emplace_back(VkDescriptorSetLayoutBinding{
		.binding = a_bind,
		.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC,
		.descriptorCount = _descriptorCount,
		.stageFlags = a_shaderFlag,
		.pImmutableSamplers = nullptr
	});
}

void VulkanShader::createDescriptorSampledImageBindings(const VkShaderStageFlags a_shaderFlag, const uint32_t a_bind, const uint32_t _descriptorCount)
{
	m_layoutBindings.emplace_back(VkDescriptorSetLayoutBinding{
		.binding = a_bind,
		.descriptorType = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,
		.descriptorCount = _descriptorCount,
		.stageFlags = a_shaderFlag,
		.pImmutableSamplers = nullptr
	});
}

void VulkanShader::createDescriptorStorageImageBindings(const VkShaderStageFlags a_shaderFlag, const uint32_t a_bind, const uint32_t _descriptorCount)
{
	m_layoutBindings.emplace_back(VkDescriptorSetLayoutBinding{
		.binding = a_bind,
		.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,
		.descriptorCount = _descriptorCount,
		.stageFlags = a_shaderFlag,
		.pImmutableSamplers = nullptr
	});
}

void VulkanShader::createDescriptorLayouts()
{
    //
}