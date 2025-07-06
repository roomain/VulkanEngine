#include "pch.h"
#include "VulkanDevice.h"
#include "VulkanSwapChain.h"
#include "VulkanMemoryCallbacks.h"
#include "ResourcesTypes/VulkanBuffers.h"


void VulkanDevice::createMemoryAllocator()
{
	static const VkAllocationCallbacks cpuAllocationCallbacks = {
		nullptr, // pUserData
		&vulkanCustom_CpuAllocation, // pfnAllocation
		&vulkanCustom_CpuReallocation, // pfnReallocation
		&vulkanCustom_CpuFree // pfnFree
	};

	static VmaVulkanFunctions vulkanFunctions
	{
		.vkGetInstanceProcAddr = vkGetInstanceProcAddr,
		.vkGetDeviceProcAddr = vkGetDeviceProcAddr
	};

	VmaAllocatorCreateInfo vmaInfo
	{
		.flags = VMA_ALLOCATOR_CREATE_EXT_MEMORY_BUDGET_BIT | VMA_ALLOCATOR_CREATE_AMD_DEVICE_COHERENT_MEMORY_BIT |
		VMA_ALLOCATOR_CREATE_BUFFER_DEVICE_ADDRESS_BIT | VMA_ALLOCATOR_CREATE_EXT_MEMORY_PRIORITY_BIT /* |
		VMA_ALLOCATOR_CREATE_KHR_EXTERNAL_MEMORY_WIN32_BIT*/,
		.physicalDevice = m_ctxt.physicalDevice,
		.device = m_ctxt.logicalDevice,
		.preferredLargeHeapBlockSize = 0,
		.pAllocationCallbacks = &cpuAllocationCallbacks,
		.pDeviceMemoryCallbacks = nullptr,
		.pHeapSizeLimit = 0,
		.pVulkanFunctions = &vulkanFunctions,
		.instance = m_ctxt.instanceHandle,
		.vulkanApiVersion = VK_API_VERSION_1_3
	};

	VK_CHECK_EXCEPT(vmaCreateAllocator(&vmaInfo, &m_memAllocator))
}

VulkanDevice::VulkanDevice(const VulkanInstanceContext& a_ctxt, const int a_devIndex, const VulkanCapabilities::VulkanDeviceConf& a_devConf, const VulkanDeviceParameter& a_param) : VulkanObject<VulkanDeviceContext>{ VulkanDeviceContext{a_ctxt} },
m_deviceCapabilities{ static_cast<uint32_t>(a_devIndex), a_devConf.physicalDev }
{
	m_ctxt.physicalDevice = a_devConf.physicalDev;
	auto features = VulkanDeviceCapabilities::toFeatures(a_param.features);

	VkDeviceCreateInfo devInfo = Vulkan::Initializers::deviceCreateInfo(a_devConf.baseCreateInfo, &features, 0/*VK_QUEUE_GRAPHICS_BIT*/);

	devInfo.enabledLayerCount = static_cast<uint32_t>(a_param.layers.size());
	const auto vCharLayer = vStringToChar(a_param.layers);
	devInfo.ppEnabledLayerNames = vCharLayer.data();
	devInfo.enabledExtensionCount = static_cast<uint32_t>(a_param.extensions.size());

	//enable layers for VMA
	auto extended = a_param.extensions;
	extended.emplace_back(VK_EXT_MEMORY_PRIORITY_EXTENSION_NAME);
	//extended.emplace_back(VK_KHR_EXTERNAL_MEMORY_WIN32_EXTENSION_NAME);
	extended.emplace_back(VK_EXT_MEMORY_BUDGET_EXTENSION_NAME);

	const auto vCharExt = vStringToChar(extended);
	devInfo.ppEnabledExtensionNames = vCharExt.data();

	m_presentationQueueIndex = a_devConf.presentationQueueIndex;
	int queueIndex = 0;
	for (const auto &familyParam : a_devConf.baseCreateInfo)
	{
		m_deviceQueues.emplace_back(QueueFamilyManager
			{
				.familyFlag = a_devConf.queueFlags[queueIndex],
				.familyIndex = familyParam.queueFamilyIndex,
				.available = familyParam.queueCount
			});
		++queueIndex;
	}

	VK_CHECK_EXCEPT(vkCreateDevice(a_devConf.physicalDev, &devInfo, nullptr, &m_ctxt.logicalDevice))
	createMemoryAllocator();	
}



VulkanDevice::~VulkanDevice()
{
	for (const auto& queueMng : m_deviceQueues)
	{
		if (!queueMng.commandBuffers.empty())
			vkFreeCommandBuffers(m_ctxt.logicalDevice, queueMng.commandPool, static_cast<uint32_t>(queueMng.commandBuffers.size()), queueMng.commandBuffers.data());

		if (queueMng.commandPool != VK_NULL_HANDLE)
			vkDestroyCommandPool(m_ctxt.logicalDevice, queueMng.commandPool, nullptr);
	}

	vmaDestroyAllocator(m_memAllocator);
	vkDestroyDevice(m_ctxt.logicalDevice, nullptr);
}

VulkanSwapChainPtr VulkanDevice::createNewSwapChain(VkSurfaceKHR a_surface, const uint32_t a_width, const uint32_t a_height)
{
	const VulkanSwapChainContext context{ m_ctxt,  a_surface };
	// because ctor is private
	m_deviceSwapChain =  std::shared_ptr<VulkanSwapChain>(new VulkanSwapChain(context, a_width, a_height));
	return m_deviceSwapChain;
}

VulkanSwapChainPtr VulkanDevice::swapChain()const
{
	return m_deviceSwapChain;
}

std::vector<VulkanDevice::QueueFamilyManager>::iterator VulkanDevice::findQueueMng(const QueueFlag a_flag)
{
	return std::ranges::find_if(m_deviceQueues, [a_flag](const auto& mng)
		{
			return (mng.familyFlag & static_cast<VkQueueFlags>(a_flag)) == static_cast<VkQueueFlags>(a_flag);
		});
}

std::vector<VulkanDevice::QueueFamilyManager>::const_iterator VulkanDevice::findQueueMng(const QueueFlag a_flag)const
{
	return std::ranges::find_if(m_deviceQueues, [a_flag](const auto& mng) 
		{
			return (mng.familyFlag & static_cast<VkQueueFlags>(a_flag)) == static_cast<VkQueueFlags>(a_flag); 
		});
}

#pragma region command
void VulkanDevice::createCommandBuffers(const QueueFlag a_flag, const uint32_t a_numBuffers)
{
	if (a_numBuffers == 0)
		return;

	if (auto iter = findQueueMng(a_flag); iter != m_deviceQueues.cend() && iter->commandPool == VK_NULL_HANDLE)
	{
		// All command buffers are allocated from a command pool
		if (iter->commandPool == VK_NULL_HANDLE)
		{
			VkCommandPoolCreateInfo commandPoolCI = Vulkan::Initializers::commandPoolCreateInfo(VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT, iter->familyIndex);
			VK_CHECK_EXCEPT(vkCreateCommandPool(m_ctxt.logicalDevice, &commandPoolCI, nullptr, &iter->commandPool))
		}

		// Allocate one command buffer per max. concurrent frame from above pool
		VkCommandBufferAllocateInfo cmdBufAllocateInfo = Vulkan::Initializers::commandBufferCreateInfo(iter->commandPool, VK_COMMAND_BUFFER_LEVEL_PRIMARY, a_numBuffers);
		const size_t offset = iter->commandBuffers.size();
		iter->commandBuffers.resize(offset + a_numBuffers);
		VK_CHECK_EXCEPT(vkAllocateCommandBuffers(m_ctxt.logicalDevice, &cmdBufAllocateInfo, iter->commandBuffers.data() + offset))
	}
}

VkQueue VulkanDevice::createQueue(const QueueFlag a_flag)
{
	if (auto iter = findQueueMng(a_flag); iter != m_deviceQueues.cend() && iter->available > 0)
	{
		VkQueue queue = VK_NULL_HANDLE;
		vkGetDeviceQueue(m_ctxt.logicalDevice, iter->familyIndex, static_cast<uint32_t>(iter->queues.size()), &queue);
		if (queue != VK_NULL_HANDLE)
		{
			iter->queues.emplace_back(queue);
			iter->available--;
		}
		return queue;
	}
	throw Exception("Can't get queue");
}

VkQueue VulkanDevice::presentationQueue(const int a_queueIndex)const
{
	VkQueue queue = VK_NULL_HANDLE;
	
	if ((m_presentationQueueIndex >= 0) && (m_deviceQueues[m_presentationQueueIndex].queues.size() > a_queueIndex))
	{
		queue = m_deviceQueues[m_presentationQueueIndex].queues[a_queueIndex];
	}
	return queue;
}

uint32_t VulkanDevice::numPresentationQueue()const
{
	return static_cast<uint32_t>(m_deviceQueues[m_presentationQueueIndex].queues.size());
}

VkQueue VulkanDevice::createPresentationQueue()
{
	if(m_presentationQueueIndex < 0)
		throw Exception("No presentation queue");

	if(m_deviceQueues[m_presentationQueueIndex].available <= 0)
		throw Exception("Can't get queue");

	VkQueue queue = VK_NULL_HANDLE;
	vkGetDeviceQueue(m_ctxt.logicalDevice, m_deviceQueues[m_presentationQueueIndex].familyIndex, static_cast<uint32_t>(m_deviceQueues[m_presentationQueueIndex].queues.size()), &queue);
	if (queue != VK_NULL_HANDLE)
	{
		m_deviceQueues[m_presentationQueueIndex].queues.emplace_back(queue);
		m_deviceQueues[m_presentationQueueIndex].available--;
	}
	return queue;

}
#pragma endregion



#pragma region image
#pragma endregion

#pragma region buffer
void VulkanDevice::createStagingBuffer(const VkDeviceSize& a_size, VulkanBuffer& a_buffer)const
{
	// don't need family index with VMA (see examples)
	VkBufferCreateInfo stagingBufInfo = Vulkan::Initializers::bufferCreateInfo(
		VkBufferCreateFlags{ 0 }, a_size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_SHARING_MODE_EXCLUSIVE,0,  nullptr);
	
	VmaAllocationCreateInfo stagingBufAllocCreateInfo = {};
	stagingBufAllocCreateInfo.usage = VMA_MEMORY_USAGE_AUTO;
	stagingBufAllocCreateInfo.flags = VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT | VMA_ALLOCATION_CREATE_MAPPED_BIT;


	VK_CHECK_EXCEPT(vmaCreateBuffer(m_memAllocator, 
		&stagingBufInfo, 
		&stagingBufAllocCreateInfo, 
		&a_buffer.m_stagingBuffer,
		&a_buffer.m_stagingBufAlloc,
		&a_buffer.m_stagingBufAllocInfo))
}
#pragma endregion