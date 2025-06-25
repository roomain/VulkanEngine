#pragma once
#pragma warning(push)
#pragma warning( disable : 4100 324 505 189 127 )
#include "vk_mem_alloc.h"
#pragma warning(pop)

struct VulkanBuffer
{
    VkBuffer m_stagingBuffer = VK_NULL_HANDLE;
    VmaAllocation m_stagingBufAlloc = VK_NULL_HANDLE;
    VmaAllocationInfo m_stagingBufAllocInfo;
};