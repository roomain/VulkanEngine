#pragma once
#include "vulkan/vulkan.h"
#include <vector>

namespace Vulkan
{
    /*@brief image with memory*/
    struct Image;
    /*@brief a pool of image with same format and size*/
    struct ImagePool;
    /*@brief represents a buffer*/
    struct Buffer;
    /*@brief represents a buffer pool*/
    struct BufferPool;

    /*@brief represents vulkan device*/
    struct Device
    {
        VkPhysicalDevice physical = VK_NULL_HANDLE;		/*!< physical device*/
        VkDevice logicalDevice = VK_NULL_HANDLE;		/*!< logical device*/
    };

    /*@brief configuration for buffer allocation*/
    struct MemoryBufferConf
    {
        VkDeviceSize size;				/*!< buffer size*/
        VkBufferUsageFlags usage;		/*!< buffer usage*/
        VkSharingMode shareMode;		/*!< share mode*/
        VkMemoryPropertyFlags memProps;	/*!< buffer memory properties*/
    };

    /*@brief configuration for buffer pool (buffers with same properties) allocation*/
    struct MemoryBufferPoolConf
    {
        std::vector<VkDeviceSize> vSize;	/*!< buffers sizes*/
        VkBufferUsageFlags usage;		    /*!< buffer usage*/
        VkSharingMode shareMode;		    /*!< share mode*/
        VkMemoryPropertyFlags memProps;	    /*!< buffer memory properties*/
    };

    /*@brief image memory configuration*/
    struct MemoryImageConf
    {
        VkImageCreateInfo imageCreateInfo;  /*!< vulkan image create conf*/
        VkMemoryPropertyFlags memProps;	    /*!< image memory properties*/
    };

    /*@brief image pool memory configuration*/
    struct MemoryImagePoolConf
    {
        std::vector<VkImageCreateInfo> vImageCreateInfo;    /*!< vulkan image create conf*/
        VkMemoryPropertyFlags memProps;	                    /*!< image memory properties*/
    };

    /*@brief represents a vulkan device with basic functionalities*/
    class VK_Device
    {
    protected:
        Device m_vkDevice;                              /*!< vulkan device*/
        VkPhysicalDeviceMemoryProperties m_memProps;    /*!< device memory properties*/

        // Memory intern functions
        /*@brief get index of compatible memory for device local memory*/
        [[nodiscard]] uint32_t memoryTypeIndex(const uint32_t a_memTypeBits, const VkMemoryPropertyFlags a_flags)const;

        [[nodiscard]] VK_Device(const Device& a_device);

    public:
        virtual ~VK_Device();
        //----------------------------------------------------------------------------------------------------
        // memory public functions
        /*@brief create a buffer*/
        void createBuffer(const MemoryBufferConf& a_memConf, Buffer& a_buffer)const;
        /*@brief create a buffer pool*/
        void createBufferPool(const MemoryBufferPoolConf& a_memConf, BufferPool& a_buffer)const;
        /*@brief create an image*/
        void createImage(const MemoryImageConf& a_memConf, Image& a_image)const;
        /*@brief create an image pool*/
        void createImagePool(const MemoryImagePoolConf& a_memConf, ImagePool& a_imagePool)const;

        // destroy

    };
}
