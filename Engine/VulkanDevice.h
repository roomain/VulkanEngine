#pragma once
/***********************************************
* @headerfile VulkanDevice.h
* @date 13 / 10 / 2024
* @author Roomain
************************************************/
#include <memory>
#include "vulkan/vulkan.hpp"

/*@brief represents a vulkan device*/
class VulkanDevice
{
	friend class VulkanContext;

private:
	VkPhysicalDevice m_physicalDevice;	/*!< vulkan physical device*/
	VkDevice m_logicalevice;			/*!< vulkan logical device*/

	VulkanDevice(const VkPhysicalDevice a_physical, const VkDevice a_logical);

public:
	VulkanDevice() = delete;
	// create buffer
	template<typename Type>
	void createBuffer(/*todo*/);
	// create mesh
	// create index buffer
	// create texture
	// create queue
	// create frame buffer
	// create shader
};

using VulkanDevicePtr = std::shared_ptr<VulkanDevice>;