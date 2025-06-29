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
#include "Parameters/VulkanParameter.h"
#include "vulkan/vulkan.hpp"
#include "VulkanObject.h"
#include "VulkanCapabilities.h"
#include "VulkanDeviceCapabilities.h"
#include "Engine_globals.h"

#pragma warning(push)
#pragma warning( disable : 4251 )

struct VulkanDeviceParameter;
struct VulkanBuffer;

class VulkanSwapChain;
using VulkanSwapChainPtr = std::shared_ptr<VulkanSwapChain>;


/*@brief represents a vulkan device*/
class VULKAN_ENGINE_LIB VulkanDevice : public VulkanObject<VulkanDeviceContext>
{
	friend class VulkanContext;

public:
	static constexpr int MAX_FRAME = 2; // why ?

private:
	VulkanDeviceCapabilities m_deviceCapabilities;					/*!< current device capabilities*/
	VulkanSwapChainPtr m_deviceSwapChain;							/*!< device swapchain*/
	VmaAllocator m_memAllocator = VK_NULL_HANDLE;

	struct QueueFamilyManager
	{
		VkQueueFlags familyFlag = 0;							/*!< queue family flag*/
		uint32_t familyIndex = 0;								/*!< queue family index*/
		uint32_t available = 0;									/*!< available queues*/
		std::vector<VkQueue> queues;							/*!< used queues*/
		VkCommandPool commandPool = VK_NULL_HANDLE;				/*!< command pool associated to queue family*/
		std::vector<VkCommandBuffer> commandBuffers;			/*!< instanciated command buffer*/
		std::vector<VkFence> waitFences;						/*!< instanciated fence*/
	};

	int32_t m_presentationQueueIndex = -1;
	std::vector<QueueFamilyManager> m_deviceQueues;	/*!< queues availables/used by device*/

	std::vector<QueueFamilyManager>::iterator findQueueMng(const QueueFlag a_flag);
	std::vector<QueueFamilyManager>::const_iterator findQueueMng(const QueueFlag a_flag)const;

	void createMemoryAllocator();

	explicit VulkanDevice(const VulkanInstanceContext& a_ctxt, const int a_devIndex, const VulkanCapabilities::VulkanDeviceConf& a_devConf, const VulkanDeviceParameter& a_param);

public:
	VulkanDevice() = delete;
	virtual ~VulkanDevice();
	[[nodiscard]] VulkanSwapChainPtr createNewSwapChain(VkSurfaceKHR a_surface, const uint32_t a_width, const uint32_t a_height);
	[[nodiscard]] VulkanSwapChainPtr swapChain()const;

#pragma region command
	void createCommandBuffers(const QueueFlag a_flag, const uint32_t a_numBuffers = 1);
	VkQueue createQueue(const QueueFlag a_flag);
	VkQueue createPresentationQueue();
	VkQueue presentationQueue(const int a_queueIndex = 0)const;
#pragma endregion


#pragma region image
	//void createImage(const uint32_t a_width, const uint32_t a_height);
#pragma endregion

#pragma region buffer
	void createStagingBuffer(const VkDeviceSize& a_size, VulkanBuffer& a_buffer)const;
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