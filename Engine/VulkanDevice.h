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
#include "VulkanDeviceCapabilities.h"

#pragma warning(push)
#pragma warning( disable : 4251 )

class VulkanSwapChain;
using VulkanSwapChainPtr = std::shared_ptr<VulkanSwapChain>;

/*@brief represents a vulkan device*/
class VULKAN_ENGINE_LIB VulkanDevice : public VulkanObject<VulkanDeviceContext>
{
	friend class VulkanContext;

private:
	VulkanDeviceCapabilities m_deviceCapabilities;					/*!< current device capabilities*/
	VulkanSwapChainPtr m_deviceSwapChain;							/*!< device swapchain*/
	explicit VulkanDevice(const VulkanDeviceContext& a_context);
	explicit VulkanDevice(VulkanDeviceContext&& a_context) noexcept;

public:
	VulkanDevice() = delete;
	virtual ~VulkanDevice() = default;
	[[nodiscard]] VulkanSwapChainPtr createNewSwapChain(const VulkanDeviceContext& a_devCtxt, VkSurfaceKHR a_surface, const uint32_t a_width, const uint32_t a_height);
	[[nodiscard]] VulkanSwapChainPtr swapChain()const;
	// create buffer
	//template<typename Type>
	//void createBuffer(/*todo*/);
	// create mesh
	// create index buffer
	// create texture
	// create queue
	//void createQueue(const VulkanQueueFamilyParameter& a_queueParam);
	// create frame buffer
	// create shader
};

using VulkanDevicePtr = std::shared_ptr<VulkanDevice>;

#pragma warning(pop)