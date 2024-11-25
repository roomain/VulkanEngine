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
#include "Engine_globals.h"


/*@brief represents a vulkan device*/
class VULKAN_ENGINE_LIB VulkanDevice
{
	friend class VulkanContext;

private:
	VkPhysicalDevice m_physicalDevice;	/*!< vulkan physical device*/
	VkDevice m_logicalevice;			/*!< vulkan logical device*/

	explicit VulkanDevice(const VkPhysicalDevice a_physicalDev, const VkDevice a_logicalDev);

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