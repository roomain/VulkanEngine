#include "pch.h"
#include <algorithm>
#include <iterator>
#include "vk_device.h"
#include "vk_ext_struct.h"

namespace Vulkan
{
    void VK_Device::createLogicalDevice(const DeviceQueuesConfiguration& a_queueConf, const std::vector<std::string>& a_deviceExt, Device& a_device)
    {
        // create queues create info for the device
        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::vector<float> vPriorities(a_queueConf.vQueueConf.size());
        std::fill(vPriorities.begin(), vPriorities.end(), 1.0f);

        int index = 0;
        for (const auto& conf : a_queueConf.vQueueConf)
        {
            auto createInfo = Initializers::queueCreateInfo();
            createInfo.queueCount = 1;
            createInfo.queueFamilyIndex = conf.index;
            createInfo.pQueuePriorities = &vPriorities[index];
            queueCreateInfos.emplace_back(std::move(createInfo));
            ++index;
        }

        // info for create logical device
        VkDeviceCreateInfo deviceCreateInfo = Initializers::deviceCreateInfo();
        deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());		// Number of Queue Create Infos
        deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();								// List of queue create infos so device can create required queues
        deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(a_deviceExt.size());			// Number of enabled logical device extensions
        std::vector<const char*> vExtNames;
        std::transform(a_deviceExt.begin(), a_deviceExt.end(), std::back_inserter(vExtNames), [](const auto& name) {return name.c_str(); });

        deviceCreateInfo.ppEnabledExtensionNames = vExtNames.data();
        VK_CHECK(vkCreateDevice(a_device.physical, &deviceCreateInfo, nullptr, &a_device.logicalDevice))
    }

    VK_Device::VK_Device(const VkPhysicalDevice a_physicalDevice) : m_vkDevice{ a_physicalDevice, VK_NULL_HANDLE }
    {
        vkGetPhysicalDeviceMemoryProperties(m_vkDevice.physical, &m_memProps);
    }

    VK_Device::~VK_Device()
    {
        if(m_vkDevice.logicalDevice != VK_NULL_HANDLE)
            vkDestroyDevice(m_vkDevice.logicalDevice, nullptr);
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

        // create image handle
        VK_CHECK(vkCreateImage(m_vkDevice.logicalDevice, &a_memConf.imageCreateInfo, nullptr, &a_image.image));

        // Get image memory requirement
        VkMemoryRequirements memoryRequirements;
        vkGetImageMemoryRequirements(m_vkDevice.logicalDevice, a_image.image, &memoryRequirements);

        // increment required memory size
        memAllocInfo.allocationSize = memoryRequirements.size;
        memAllocInfo.memoryTypeIndex = memoryTypeIndex(memoryRequirements.memoryTypeBits, a_memConf.memProps);
        VK_CHECK(vkAllocateMemory(m_vkDevice.logicalDevice, &memAllocInfo, nullptr, &a_image.memory));
        VK_CHECK(vkBindImageMemory(m_vkDevice.logicalDevice, a_image.image, a_image.memory, 0));
    }

    void VK_Device::createImagePool(const MemoryImagePoolConf& a_memConf, ImagePool& a_imagePool)const
    {
        a_imagePool.images.resize(a_memConf.vImageCreateInfo.size());
        VkMemoryAllocateInfo memAllocInfo = Vulkan::Initializers::memoryAllocateInfo();
        memAllocInfo.memoryTypeIndex = 0;
        bool bMemFound = false;
        unsigned int index = 0;
        std::vector<VkDeviceSize> imageOffset;
        for (auto& info : a_memConf.vImageCreateInfo)
        {
            // create image handle
            VK_CHECK(vkCreateImage(m_vkDevice.logicalDevice, &info, nullptr, &a_imagePool.images[index].image));

            // Get image memory requirement
            VkMemoryRequirements memoryRequirements;
            vkGetImageMemoryRequirements(m_vkDevice.logicalDevice, a_imagePool.images[index].image, &memoryRequirements);

            memAllocInfo.allocationSize += memoryRequirements.size;

            // Get memory offset for image
            imageOffset.emplace_back(memAllocInfo.allocationSize);

            if (!bMemFound)
            {
                memAllocInfo.memoryTypeIndex = memoryTypeIndex(memoryRequirements.memoryTypeBits, a_memConf.memProps);
                bMemFound = true;
            }
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

    void VK_Device::createImagePool(const MemorySameImagePoolConf& a_memConf, ImagePool& a_imagePool)const
    {
        a_imagePool.images.resize(a_memConf.imageCount);
        VkMemoryAllocateInfo memAllocInfo = Vulkan::Initializers::memoryAllocateInfo();
        memAllocInfo.memoryTypeIndex = 0;
        unsigned int index = 0;


        // Get image memory requirement
        VkMemoryRequirements memoryRequirements;
        VkDeviceSize imageOffset;
        for (unsigned int iCount = 0; iCount < a_memConf.imageCount; ++iCount)
        {
            // create image handle
            VK_CHECK(vkCreateImage(m_vkDevice.logicalDevice, &a_memConf.imageCreateInfo, nullptr, &a_imagePool.images[index].image));
            if (memAllocInfo.allocationSize == 0)
            {
                vkGetImageMemoryRequirements(m_vkDevice.logicalDevice, a_imagePool.images[index].image, &memoryRequirements);
                memAllocInfo.allocationSize = memoryRequirements.size;
                memAllocInfo.memoryTypeIndex = memoryTypeIndex(memoryRequirements.memoryTypeBits, a_memConf.memProps);
            }
        }

        imageOffset = memAllocInfo.allocationSize;
        memAllocInfo.allocationSize *= a_memConf.imageCount;
        VK_CHECK(vkAllocateMemory(m_vkDevice.logicalDevice, &memAllocInfo, nullptr, &a_imagePool.memory));

        // bind memory for each image
        index = 0;
        for (BaseImage& img : a_imagePool.images)
        {
            VK_CHECK(vkBindImageMemory(m_vkDevice.logicalDevice, img.image, a_imagePool.memory, imageOffset));
            imageOffset += imageOffset;
            ++index;
        }
    }

    void VK_Device::destroyBaseImage(BaseImage& a_toDestroy)const
    {

        if (a_toDestroy.imageView != VK_NULL_HANDLE)
            vkDestroyImageView(m_vkDevice.logicalDevice, a_toDestroy.imageView, nullptr);
        a_toDestroy.imageView = VK_NULL_HANDLE;


        if (a_toDestroy.image != VK_NULL_HANDLE)
            vkDestroyImage(m_vkDevice.logicalDevice, a_toDestroy.image, nullptr);
        a_toDestroy.image = VK_NULL_HANDLE;
    }

    void VK_Device::destroyImage(Image& a_toDestroy)const
    {
        destroyBaseImage(a_toDestroy);
        vkFreeMemory(m_vkDevice.logicalDevice, a_toDestroy.memory, nullptr);
    }

    void VK_Device::destroyImagePool(ImagePool& a_toDestroy)const
    {
        for (auto& image : a_toDestroy.images)
            destroyBaseImage(image);

        vkFreeMemory(m_vkDevice.logicalDevice, a_toDestroy.memory, nullptr);
        a_toDestroy.memory = VK_NULL_HANDLE;
    }

    void VK_Device::destroyBuffer(Buffer& a_toDestroy)const
    {
        vkDestroyBuffer(m_vkDevice.logicalDevice, a_toDestroy.buffer, nullptr);
        a_toDestroy.buffer = VK_NULL_HANDLE;
        vkFreeMemory(m_vkDevice.logicalDevice, a_toDestroy.memory, nullptr);
        a_toDestroy.memory = VK_NULL_HANDLE;
    }

    void VK_Device::destroyBufferPool(BufferPool& a_toDestroy)const
    {
        for (auto& buffer : a_toDestroy.vbuffer)
            vkDestroyBuffer(m_vkDevice.logicalDevice, buffer, nullptr);
        vkFreeMemory(m_vkDevice.logicalDevice, a_toDestroy.memory, nullptr);
    }

    void VK_Device::createImageView(const VkImage a_image, const VkFormat a_format, const VkImageAspectFlags a_aspectFlags, VkImageView& a_imgView)
    {
        VkImageViewCreateInfo viewCreateInfo = Vulkan::Initializers::imageViewCreateInfo();
        viewCreateInfo.image = a_image;											// Image to create view for
        viewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;						// Type of image (1D, 2D, 3D, Cube, etc)
        viewCreateInfo.format = a_format;										// Format of image data
        viewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;			// Allows remapping of rgba components to other rgba values
        viewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        viewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        viewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

        // Subresources allow the view to view only a part of an image
        viewCreateInfo.subresourceRange.aspectMask = a_aspectFlags;				// Which aspect of image to view (e.g. COLOR_BIT for viewing colour)
        viewCreateInfo.subresourceRange.baseMipLevel = 0;						// Start mipmap level to view from
        viewCreateInfo.subresourceRange.levelCount = 1;							// Number of mipmap levels to view
        viewCreateInfo.subresourceRange.baseArrayLayer = 0;						// Start array level to view from
        viewCreateInfo.subresourceRange.layerCount = 1;							// Number of array levels to view

        VK_CHECK(vkCreateImageView(m_vkDevice.logicalDevice, &viewCreateInfo, nullptr, &a_imgView))
    }

}