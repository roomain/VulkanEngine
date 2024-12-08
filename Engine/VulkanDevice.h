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
#include "VulkanObject.h"
#include "Engine_globals.h"


/*@brief represents a vulkan device*/
class VULKAN_ENGINE_LIB VulkanDevice : public VulkanObject<VulkanDeviceContext>
{
	friend class VulkanContext;

private:
	explicit VulkanDevice(const VulkanDeviceContext& a_context);
	explicit VulkanDevice(VulkanDeviceContext&& a_context) noexcept;

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