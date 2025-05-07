#pragma once
/***********************************************
* @headerfile VulkanCache.h
* @date 04 / 05 / 2025
* @author Roomain
************************************************/
#include <string>
#include <array>
#include "vulkan/vulkan.h"
#include "VulkanObject.h"

class VulkanPipelineCache : public VulkanObject<VulkanDeviceContext>
{
    friend class VulkanPipeline;
private:
    struct VkPipelineCacheHeader
    {
        uint32_t headerSize;
        uint32_t headerVersion;
        uint32_t vendorID;
        uint32_t deviceID;
        std::array<uint8_t, 16> pipelineCacheUUID;
    };


    VkPipelineCache m_cache = VK_NULL_HANDLE;
    bool checkCache(const VkPipelineCacheHeader& a_header);
    void cleanup();

public:
    VulkanPipelineCache(const VulkanDeviceContext& a_ctxt);
    ~VulkanPipelineCache();
    bool loadCache(const std::string& a_filename);
    bool saveCache(const std::string& a_filename);
};