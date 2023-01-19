#include "pch.h"
#include "vk_device.h"

namespace Vulkan
{
    VK_Device::VK_Device(const Device& a_device) : m_vkDevice{ a_device }
    {
        vkGetPhysicalDeviceMemoryProperties(m_vkDevice.physical, &m_memProps);
    }

    VK_Device::~VK_Device()
    {

        //
    }

    uint32_t VK_Device::memoryTypeIndex(const uint32_t a_memTypeBits, const VkMemoryPropertyFlags a_flags)const
    {
        for (uint32_t iIndex = 0; iIndex < m_memProps.memoryTypeCount; iIndex++)
        {
            if ((a_memTypeBits & (1 << iIndex))														// Index of memory type must match corresponding bit in allowedTypes
                && (m_memProps.memoryTypes[iIndex].propertyFlags & a_flags) == a_flags)		// Desired property bit flags are part of memory type's property flags
            {
                // This memory type is valid, so return its index
                return iIndex;
            }
        }
        throw Vulkan::VK_Exception("Can't find Memory index.", std::source_location::current());
    }

    void VK_Device::createBuffer(const MemoryBufferConf& a_memConf, Buffer& a_buffer)const
    {
        VkBufferCreateInfo bufferInfo = Initializers::bufferCreateInfo();
        bufferInfo.size = a_memConf.size;							// Size of buffer (size of 1 vertex * number of vertices)
        bufferInfo.usage = a_memConf.usage;							// Multiple types of buffer possible
        bufferInfo.sharingMode = a_memConf.shareMode;				// Similar to Swap Chain images, can share vertex buffer

        VK_CHECK(vkCreateBuffer(m_vkDevice.logicalDevice, &bufferInfo, nullptr, &a_buffer.buffer));

        // Get buffer memory requirements
        VkMemoryRequirements memRequirements;
        vkGetBufferMemoryRequirements(m_vkDevice.logicalDevice, a_buffer.buffer, &memRequirements);

        // allocate memory
        VkMemoryAllocateInfo memAllocInfo = Vulkan::Initializers::memoryAllocateInfo();
        memAllocInfo.allocationSize = a_memConf.size;
        memAllocInfo.memoryTypeIndex = memoryTypeIndex(memRequirements.memoryTypeBits, a_memConf.memProps);
        VK_CHECK(vkAllocateMemory(m_vkDevice.logicalDevice, &memAllocInfo, nullptr, &a_buffer.memory));

        // Allocate memory to given vertex buffer at offset 0
        vkBindBufferMemory(m_vkDevice.logicalDevice, a_buffer.buffer, a_buffer.memory, 0);
    }

    void VK_Device::createBufferPool(const MemoryBufferPoolConf& a_memConf, BufferPool& a_buffer)const
    {
        VkBufferCreateInfo bufferInfo = Initializers::bufferCreateInfo();
        bufferInfo.size = 0;							// Size of buffer (size of 1 vertex * number of vertices)
        bufferInfo.usage = a_memConf.usage;				// Multiple types of buffer possible
        bufferInfo.sharingMode = a_memConf.shareMode;	// Similar to Swap Chain images, can share vertex buffer
        a_buffer.vbuffer.resize(a_memConf.vSize.size());
        VkMemoryAllocateInfo memAllocInfo = Vulkan::Initializers::memoryAllocateInfo();
        memAllocInfo.allocationSize = 0;
        int index = 0;
        for (auto& size : a_memConf.vSize)
        {
            bufferInfo.size = size;
            memAllocInfo.allocationSize += size;
            VK_CHECK(vkCreateBuffer(m_vkDevice.logicalDevice, &bufferInfo, nullptr, &a_buffer.vbuffer[index]));
            ++index;
        }

        // Get buffer memory requirements
        VkMemoryRequirements memRequirements;
        vkGetBufferMemoryRequirements(m_vkDevice.logicalDevice, a_buffer.vbuffer[0], &memRequirements);
        memAllocInfo.memoryTypeIndex = memoryTypeIndex(memRequirements.memoryTypeBits, a_memConf.memProps);
        VK_CHECK(vkAllocateMemory(m_vkDevice.logicalDevice, &memAllocInfo, nullptr, &a_buffer.memory));
        index = 0;
        VkDeviceSize bufferOffset = 0;

        // bind memory for each buffers
        for (auto& buffer : a_buffer.vbuffer)
        {
            vkBindBufferMemory(m_vkDevice.logicalDevice, buffer, a_buffer.memory, bufferOffset);
            bufferOffset += a_memConf.vSize[index];
            ++index;
        }
    }

    void VK_Device::createImage(const MemoryImageConf& a_memConf, Image& a_image)const
    {
        VkMemoryAllocateInfo memAllocInfo = Vulkan::Initializers::memoryAllocateInfo();
        uint32_t memTypeBit = 0;
        // create image handle
        VK_CHECK(vkCreateImage(m_vkDevice.logicalDevice, &a_memConf.imageCreateInfo, nullptr, &a_image.image));

        // Get image memory requirement
        VkMemoryRequirements memoryRequirements;
        vkGetImageMemoryRequirements(m_vkDevice.logicalDevice, a_image.image, &memoryRequirements);

        // increment required memory size
        memAllocInfo.allocationSize = memoryRequirements.size;
        memAllocInfo.memoryTypeIndex = memoryTypeIndex(memRequirements.memoryTypeBits, a_memConf.memProps);
        VK_CHECK(vkAllocateMemory(m_vkDevice.logicalDevice, &memAllocInfo, nullptr, &a_image.memory));
        VK_CHECK(vkBindImageMemory(m_vkDevice.logicalDevice, a_image.image, a_image.memory, 0));
    }

    void VK_Device::createImagePool(const MemoryImagePoolConf& a_memConf, ImagePool& a_imagePool)const
    {
        a_imagePool.images.resize(a_memConf.vImageCreateInfo.size());
        VkMemoryAllocateInfo memAllocInfo = Vulkan::Initializers::memoryAllocateInfo();
        memAllocInfo.memoryTypeIndex = -1;
        unsigned int index = 0;
        std::vector<VkDeviceSize> imageOffset;
        for (auto info : a_memConf.vImageCreateInfo)
        {
            // create image handle
            VK_CHECK(vkCreateImage(m_vkDevice.logicalDevice, &a_memConf.imageCreateInfo, nullptr, &a_imagePool.images[index].image));

            // Get image memory requirement
            VkMemoryRequirements memoryRequirements;
            vkGetImageMemoryRequirements(m_vkDevice.logicalDevice, a_image.image, &memoryRequirements);

            memAllocInfo.allocationSize += memoryRequirements.size;

            // Get memory offset for image
            imageOffset.emplace_back(memAllocInfo.allocationSize);

            if (memAllocInfo.memoryTypeIndex > -1)
                memAllocInfo.memoryTypeIndex = memoryTypeIndex(memRequirements.memoryTypeBits, a_memConf.memProps);
        }

        VK_CHECK(vkAllocateMemory(m_vkDevice.logicalDevice, &memAllocInfo, nullptr, &a_imagePool.memory));

        // bind memory for each image
        index = 0;
        for (BaseImage& img : a_imagePool.images)
        {
            VK_CHECK(vkBindImageMemory(m_vkDevice.logicalDevice, img.image, a_imagePool.memory, imageOffset[index]));
            ++index;
        }
    }


}