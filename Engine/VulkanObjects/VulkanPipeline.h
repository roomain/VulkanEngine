#pragma once
/***********************************************
* @headerfile VulkanPipeline.h
* @date 25 / 02 / 2025
* @author Roomain
************************************************/
#include <vector>
#include <memory>
#include <vulkan/vulkan.hpp>
#include "VulkanObject.h"
#include "common/notCopiable.h"
#include "VulkanLocalsContexts.h"
#include "VulkanShader.h"



/*@brief represents a vulkan pipeline*/
class VulkanPipeline : public VulkanObject<VulkanDeviceContext>
{
private:
	int m_depthAttachmentIndex = -1;										/*!< index of depth attachment in m_attachment*/
	std::vector<VkAttachmentDescription> m_attachement;						/*!< list of attachment*/
	std::vector<VkPipelineShaderStageCreateInfo> m_shaderStageCreateInfo;
	VkPipeline m_pipeline = VK_NULL_HANDLE;
	VkPipelineCache m_pipelineCache = VK_NULL_HANDLE;
	std::shared_ptr<VulkanShader> m_shader;
	VkDescriptorSetLayout m_descriptorSetLayout = VK_NULL_HANDLE;
	VkPipelineLayout m_pipelineLayout = VK_NULL_HANDLE;

	// vulkan graphics pipeline parameters
	VkPrimitiveTopology m_topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;	/*!< primitive topology*/
	DepthStencilSettings m_depthSettings;									/*!< depth settings*/
	RasterizationSettings m_rasterSettings;									/*!< raster settings*/
	std::vector<VkDynamicState> m_dynamicStateEnables;						/*!< pipeline dynamic states*/
	uint32_t m_pathCtrlPoints = 0;											/*!< number of control point useles if m_topology != VK_PRIMITIVE_TOPOLOGY_PATCH_LIST*/
	uint32_t m_viewportCount = 1;
	uint32_t m_scissorCount = 1;
	

protected:
	virtual void setupRenderPass(VkRenderPass& a_renderPass);


public:

	NOT_COPIABLE(VulkanPipeline)
	explicit VulkanPipeline(const VulkanDeviceContext& a_ctxt);
	virtual ~VulkanPipeline();
	inline std::shared_ptr<VulkanShader> shader()const { return m_shader; }
	void setShader(const std::shared_ptr<VulkanShader>& a_shader);
	virtual void bind(VkCommandBuffer& a_cmdBuffer)const;

	void cleanup();
	void setPrimitiveTopology(const VkPrimitiveTopology a_topology)
	{
		m_topology = a_topology;
	}

	void setDepthSettings(const DepthStencilSettings& a_settings)
	{
		m_depthSettings = a_settings;
	}

	void setRasterSettings(const RasterizationSettings& a_settings)
	{
		m_rasterSettings = a_settings;
	}

	void setDynamicStates(const std::vector<VkDynamicState>& a_states)
	{
		m_dynamicStateEnables = a_states;
	}

	void setNumTopologyCtrlPoint(const uint32_t a_count)
	{
		m_pathCtrlPoints = a_count;
	}

	void setViewportCount(const uint32_t a_count)
	{
		m_viewportCount = a_count;
	}

	void setScissorCount(const uint32_t a_count)
	{
		m_scissorCount = a_count;
	}

	template<typename VertexType>
	static VkPipelineVertexInputStateCreateInfo setupPipelineVertexInput()
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
		return vertexInput;
	}


	template<typename VertexType>
	bool create(const VkPipelineVertexInputStateCreateInfo& a_vertexInput)
	{
		if (m_shader)
		{
			VkRenderPass renderPass;
			setupRenderPass(renderPass);
			// bingings
			VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCi = Vulkan::Initializers::descriptorSetLayoutCreateInfo(
				m_shader->m_layoutBindings.data(), static_cast<uint32_t>(m_shader->m_layoutBindings.size()));
			VK_CHECK_EXCEPT(vkCreateDescriptorSetLayout(m_ctxt.logicalDevice, &descriptorSetLayoutCi, nullptr,
				&m_descriptorSetLayout));

			VkPipelineLayoutCreateInfo pipelineLayoutCi = Vulkan::Initializers::pipelineLayoutCreateInfo(m_descriptorSetLayout);
			VK_CHECK_EXCEPT(vkCreatePipelineLayout(m_ctxt.logicalDevice, &pipelineLayoutCi, nullptr, &m_pipelineLayout));

			// assembly
			VkPipelineInputAssemblyStateCreateInfo inputAssemblyState = Vulkan::Initializers::pipelineInputAssemblyStateCreateInfo(m_topology, 0, VK_TRUE);

			// tesselation type
			VkPipelineTessellationStateCreateInfo* tessellationStateRef = nullptr;
			VkPipelineTessellationStateCreateInfo tessellationState;
			if (m_topology == VK_PRIMITIVE_TOPOLOGY_PATCH_LIST)
			{
				tessellationState = Vulkan::Initializers::pipelineTessellationStateCreateInfo(m_pathCtrlPoints);
				tessellationStateRef = &tessellationState;
			}

			VkPipelineViewportStateCreateInfo viewportState = Vulkan::Initializers::pipelineViewportStateCreateInfo(m_viewportCount, m_scissorCount);
			VkPipelineRasterizationStateCreateInfo rasterizationState = Vulkan::Initializers::pipelineRasterizationStateCreateInfo(m_rasterSettings);
			VkPipelineMultisampleStateCreateInfo multisampleState = Vulkan::Initializers::pipelineMultisampleStateCreateInfo(VK_SAMPLE_COUNT_1_BIT);
			VkPipelineDepthStencilStateCreateInfo depthStencilState = Vulkan::Initializers::pipelineDepthStencilStateCreateInfo(m_depthSettings);

			VkPipelineColorBlendAttachmentState blendAttachmentState = Vulkan::Initializers::pipelineColorBlendAttachmentState(0xf, VK_FALSE);
			VkPipelineColorBlendStateCreateInfo colorBlendState = Vulkan::Initializers::pipelineColorBlendStateCreateInfo(1, &blendAttachmentState);

			VkPipelineDynamicStateCreateInfo dynamicState = Vulkan::Initializers::pipelineDynamicStateCreateInfo(m_dynamicStateEnables);

			VkGraphicsPipelineCreateInfo pipelineCi = Vulkan::Initializers::createGraphicPipeline(
				0,
				m_shader->m_shaderStageCreateInfo,
				&a_vertexInput,
				&inputAssemblyState,
				tessellationStateRef,
				&viewportState,
				&rasterizationState,
				&multisampleState,
				&depthStencilState,
				&colorBlendState,
				&dynamicState,
				m_pipelineLayout,
				renderPass,
				0,
				VK_NULL_HANDLE,
				-1
			);

			//if (m_pipelineCache == VK_NULL_HANDLE)
			//{
			//	VkPipelineCacheCreateInfo pipelineCacheCreateInfo = {};
			//	pipelineCacheCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
			//	VK_CHECK_LOG(vkCreatePipelineCache(m_ctxt.logicalDevice, &pipelineCacheCreateInfo, nullptr, &m_pipelineCache));
			//}

			VK_CHECK_EXCEPT(vkCreateGraphicsPipelines(m_ctxt.logicalDevice, m_pipelineCache, 1, &pipelineCi, nullptr, &m_pipeline))

			return true;
		}
		return false;
	}

	void addAttachment(const VkAttachmentDescription& a_attachement);
	void setDepthAttachment(const VkAttachmentDescription& a_attachement);
};
