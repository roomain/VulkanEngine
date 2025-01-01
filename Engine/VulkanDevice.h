#pragma once
/***********************************************
* @headerfile VulkanDevice.h
* @date 13 / 10 / 2024
* @author Roomain
************************************************/

#pragma warning(push)
#pragma warning( disable : 4100 324 505 189 127 )
#include "vk_mem_alloc.h"
#pragma warning(pop)

#include <memory>
#include <vector>
#include <array>
#include <unordered_map>
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

public:
	static constexpr int MAX_FRAME = 2;

private:
	VulkanDeviceCapabilities m_deviceCapabilities;					/*!< current device capabilities*/
	VulkanSwapChainPtr m_deviceSwapChain;							/*!< device swapchain*/
	VmaAllocator m_memAllocator = VK_NULL_HANDLE;

	struct AvailableQueues
	{
		uint32_t familyIndex;							/*!< queue family index*/
		int available;									/*!< available queues*/
		std::vector<VkQueue> queues;					/*!< used queues*/
		VkCommandPool m_commandPool = VK_NULL_HANDLE;	/*!< command pool associated to queue family*/
		std::array<VkCommandBuffer, MAX_FRAME> commandBuffers;
		std::array<VkFence, MAX_FRAME> waitFences;
	};
	std::unordered_map<QueueFlag, AvailableQueues> m_deviceQueues;	/*!< queues availables/used by device*/
	void createMemoryAllocator();

	explicit VulkanDevice(const VulkanDeviceContext& a_context);
	explicit VulkanDevice(VulkanDeviceContext&& a_context) noexcept;

public:
	VulkanDevice() = delete;
	virtual ~VulkanDevice() = default;
	[[nodiscard]] VulkanSwapChainPtr createNewSwapChain(const VulkanDeviceContext& a_devCtxt, VkSurfaceKHR a_surface, const uint32_t a_width, const uint32_t a_height);
	[[nodiscard]] VulkanSwapChainPtr swapChain()const;

#pragma region command
	void createCommandBuffers(const QueueFlag a_flag);
	VkQueue createQueue(const QueueFlag a_flag);
#pragma endregion

#pragma region shader
	VkShaderModule loadSPIRVShader(const std::string& a_filename)const;
#pragma endregion

#pragma region image
#pragma endregion

#pragma region buffer
#pragma endregion
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