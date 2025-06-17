#pragma once
/***********************************************
* @headerfile VulkanShader.h
* @date 27 / 04 / 2025
* @author Roomain
************************************************/
#include <vector>
#include <memory>
#include <unordered_map>
#include <vulkan/vulkan.hpp>
#include "VulkanObject.h"
#include "common/notCopiable.h"

/*@brief*/
class VulkanShader : public VulkanObject<VulkanDeviceContext>
{
    friend class VulkanPipeline;
private:

   /*struct VulkanShaderModule
    {
        VkShaderModule m_shaderModules = VK_NULL_HANDLE;
        VkDescriptorSetLayout m_descriptorLayout = VK_NULL_HANDLE;
        VkDescriptorSetLayoutBinding m_layoutBinding = VK_NULL_HANDLE;
    };*/

	std::vector<VkPipelineShaderStageCreateInfo> m_shaderStageCreateInfo;
    std::unordered_map<VkShaderStageFlagBits, VkShaderModule> m_mpShaderModules;
    std::vector<VkDescriptorSetLayoutBinding> m_layoutBindings;

public:
    NOT_COPIABLE(VulkanShader)
    VulkanShader(const VulkanDeviceContext& a_ctxt);
    virtual ~VulkanShader();
    void cleanup();
    void loadShaderSpirV(const std::string& a_filename, const VkShaderStageFlagBits a_stage);
    void createDescriptorUniformTexelBufferBindings(const VkShaderStageFlags a_shaderFlag, const uint32_t a_bind, const uint32_t _descriptorCount = 1);
    void createDescriptorStorageTexelBufferBindings(const VkShaderStageFlags a_shaderFlag, const uint32_t a_bind, const uint32_t _descriptorCount = 1);
    void createDescriptorUniformBufferBindings(const VkShaderStageFlags a_shaderFlag, const uint32_t a_bind, const uint32_t _descriptorCount = 1);
    void createDescriptorStorageBufferBindings(const VkShaderStageFlags a_shaderFlag, const uint32_t a_bind, const uint32_t _descriptorCount = 1);
    void createDescriptorUniformBufferDynBindings(const VkShaderStageFlags a_shaderFlag, const uint32_t a_bind, const uint32_t _descriptorCount = 1);
    void createDescriptorStorageBufferDynBindings(const VkShaderStageFlags a_shaderFlag, const uint32_t a_bind, const uint32_t _descriptorCount = 1);
    void createDescriptorSampledImageBindings(const VkShaderStageFlags a_shaderFlag, const uint32_t a_bind, const uint32_t _descriptorCount = 1);
    void createDescriptorStorageImageBindings(const VkShaderStageFlags a_shaderFlag, const uint32_t a_bind, const uint32_t _descriptorCount = 1);
    void createDescriptorLayouts();
};

using VulkanShaderPtr = std::shared_ptr<VulkanShader>;