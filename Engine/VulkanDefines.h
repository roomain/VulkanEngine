#pragma once
#include <vector>
#include <array>
#include <vulkan/vulkan.hpp>

using VkCommandBufferVector = std::vector<VkCommandBuffer>;
template<std::size_t Count>
using  VkCommandBufferVectorArray = std::array<VkCommandBuffer, Count>;

using VkPipelineStageFlagsVector = std::vector<VkPipelineStageFlags>;
template<std::size_t Count>
using  VkPipelineStageFlagsArray = std::array<VkPipelineStageFlags, Count>;

using  SemaphoreVector = std::vector<VkSemaphore>;
template<std::size_t Count>
using  SemaphoreArray = std::array<VkSemaphore, Count>;

using VertexInputBindingDescVector = std::vector<VkVertexInputBindingDescription>;
template<std::size_t Count>
using VertexInputBindingDescArray = std::array<VkVertexInputBindingDescription, Count>;

using VertexInputAttribDescVector = std::vector<VkVertexInputAttributeDescription>;
template<std::size_t Count>
using VertexInputAttribDescArray = std::array<VkVertexInputAttributeDescription, Count>;

