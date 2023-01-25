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

    struct DeviceQueuesConfiguration;

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
        std::vector<VkImageCreateInfo> vImageCreateInfo;    /*!< list of vulkan image create conf*/
        VkMemoryPropertyFlags memProps;	                    /*!< image memory properties*/
    };

    /*@brief image pool memory configuration with same image parameter*/
    struct MemorySameImagePoolConf
    {
        unsigned int imageCount;                            /*!< number of images to create*/
        VkImageCreateInfo imageCreateInfo;                  /*!< vulkan image create conf*/
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

        [[nodiscard]] explicit VK_Device(const VkPhysicalDevice a_physicalDevice);

        static void createLogicalDevice(const DeviceQueuesConfiguration& a_queueConf, const std::vector<std::string>& a_deviceExt, Device& a_device);

    private:
        void destroyBaseImage(BaseImage& a_toDestroy)const;

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
        void createImagePool(const MemorySameImagePoolConf& a_memConf, ImagePool& a_imagePool)const;

        /*@brief destroy Image and release memory*/
        void destroyImage(Image& a_toDestroy)const;
        /*@brief destroy ImagePool and release memory*/
        void destroyImagePool(ImagePool& a_toDestroy)const;
        /*@brief destroy Buffer and release memory*/
        void destroyBuffer(Buffer& a_toDestroy)const;
        /*@brief destroy BufferPool and release memory*/
        void destroyBufferPool(BufferPool& a_toDestroy)const;
        //-----------------------------------------------------------------------------------------------------
        void createImageView(const VkImage a_image, const VkFormat a_format, const VkImageAspectFlags a_aspectFlags, VkImageView& a_imgView)const;
        void createBufferView(const VkBufferViewCreateFlags a_flag, const VkBuffer a_bufferHandle, const VkFormat a_format, const VkDeviceSize& a_offset, const VkDeviceSize& a_range, VkBufferView& a_buffView)const;
    };
}
