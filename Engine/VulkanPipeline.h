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


/*@brief represents a vulkan pipeline*/
class VulkanPipeline : public VulkanObject<VulkanDeviceContext>
{
private:
	int m_depthAttachmentIndex = -1;										/*!< index of depth attachment in m_attachment*/
	std::vector<VkAttachmentDescription> m_attachement;						/*!< list of attachment*/
	std::vector<VkPipelineShaderStageCreateInfo> m_shaderStageCreateInfo;
	VkPipeline m_pipeline = VK_NULL_HANDLE;
	// todo shaders modules
	//

protected:
	virtual void setupRenderPass(VkRenderPass& a_renderPass);

public:
	VulkanPipeline(const VulkanDeviceContext& a_ctxt);
	virtual ~VulkanPipeline();

	void loadShaderSpirV(const std::string& a_filename, const VkShaderStageFlagBits a_stage);

	void cleanup();
	void create();

	void addAttachment(const VkAttachmentDescription& a_attachement);
	void setDepthAttachment(const VkAttachmentDescription& a_attachement);

	// todo
};
