#pragma once
/***********************************************
* @headerfile VulkanDevice.h
* @date 13 / 10 / 2024
* @author Roomain
************************************************/
#include <memory>
#include <vector>
#include "VulkanParameter.h"
#include "vulkan/vulkan.hpp"

struct VulkanQueueCreateInfo
{
	uint32_t queueIndex;
	VkQueueFlags flags;
	uint32_t queueCount;
};

struct VulkanDeviceCreateInfo
{
	VkPhysicalDevice physicalDevice;
	VkDevice logicalDevice;
	std::vector<VulkanQueueCreateInfo> queuesInfo;
};

/*@brief represents a vulkan device*/
class VulkanDevice
{
	friend class VulkanContext;

private:
	VkPhysicalDevice m_physicalDevice;	/*!< vulkan physical device*/
	VkDevice m_logicalevice;			/*!< vulkan logical device*/

	explicit VulkanDevice(const VulkanDeviceCreateInfo& a_createInfo);

public:
	VulkanDevice() = delete;
	// create buffer
	template<typename Type>
	void createBuffer(/*todo*/);
	// create mesh
	// create index buffer
	// create texture
	// create queue
	//void createQueue(const VulkanQueueFamilyParameter& a_queueParam);
	// create frame buffer
	// create shader
};

using VulkanDevicePtr = std::shared_ptr<VulkanDevice>;