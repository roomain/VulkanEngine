#include "pch.h"
#include "VulkanDevice.h"
#include "VulkanSwapChain.h"

void VulkanDevice::createMemoryAllocator()
{
	/*VmaAllocatorCreateInfo vmaInfo
	{
		.flags,
		.physicalDevice = a_context.physicalDevice,
		.device = a_context.logicalDevice,
		.preferredLargeHeapBlockSize,
		.pAllocationCallbacks,
		.pDeviceMemoryCallbacks,
		.pHeapSizeLimit,
		.pVulkanFunctions,
		.instance = a_context.instanceHandle,
		.vulkanApiVersion = VK_VERSION_1_3
	};
	////todo
	vmaCreateAllocator(&vmaInfo, &m_memAllocator);*/
}

VulkanDevice::VulkanDevice(const VulkanInstanceContext& a_ctxt, const int a_devIndex, const VulkanCapabilities::VulkanDeviceConf& a_devConf, const VulkanDeviceParameter& a_param) : VulkanObject<VulkanDeviceContext>{ VulkanDeviceContext{a_ctxt} },
m_deviceCapabilities{ static_cast<uint32_t>(a_devIndex), a_devConf.physicalDev }
{
	auto vExtents = vStringToChar(a_param.extensions);
	auto vLayers = vStringToChar(a_param.layers);
	auto features = VulkanDeviceCapabilities::toFeatures(a_param.features);

	VkDeviceCreateInfo devInfo = Vulkan::Initializers::deviceCreateInfo(a_devConf.baseCreateInfo, a_param.extensions, a_param.layers, &features, VK_QUEUE_GRAPHICS_BIT);

	devInfo.pEnabledFeatures = &features;

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

	// todo
	vkDestroyDevice(m_ctxt.logicalDevice, nullptr);
}

VulkanSwapChainPtr VulkanDevice::createNewSwapChain(const VulkanDeviceContext& a_devCtxt, VkSurfaceKHR a_surface, const uint32_t a_width, const uint32_t a_height)
{
	const VulkanSwapChainContext context{ a_devCtxt,  a_surface };
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
void VulkanDevice::createCommandBuffers(const QueueFlag a_flag)
{
	if (auto iter = findQueueMng(a_flag); iter != m_deviceQueues.cend() && iter->commandPool == VK_NULL_HANDLE)
	{
		// All command buffers are allocated from a command pool
		VkCommandPoolCreateInfo commandPoolCI = Vulkan::Initializers::commandPoolCreateInfo(VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT, iter->familyIndex);
		VK_CHECK_EXCEPT(vkCreateCommandPool(m_ctxt.logicalDevice, &commandPoolCI, nullptr, &iter->commandPool))

		// Allocate one command buffer per max. concurrent frame from above pool
		VkCommandBufferAllocateInfo cmdBufAllocateInfo = Vulkan::Initializers::commandBufferCreateInfo(iter->commandPool, VK_COMMAND_BUFFER_LEVEL_PRIMARY, VulkanDevice::MAX_FRAME);
		VK_CHECK_EXCEPT(vkAllocateCommandBuffers(m_ctxt.logicalDevice, &cmdBufAllocateInfo, iter->commandBuffers.data()))
	}
}

VkQueue VulkanDevice::createQueue(const QueueFlag a_flag)
{
	if (auto iter = findQueueMng(a_flag); iter != m_deviceQueues.cend() && iter->available > 0)
	{
		VkQueue queue;
		vkGetDeviceQueue(m_ctxt.logicalDevice, iter->familyIndex, static_cast<uint32_t>(iter->queues.size()), &queue);
		iter->queues.emplace_back(queue);
		iter->available--;
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

VkQueue VulkanDevice::createPresentationQueue()
{
	if(m_presentationQueueIndex < 0)
		throw Exception("No presentation queue");

	if(m_deviceQueues[m_presentationQueueIndex].available <= 0)
		throw Exception("Can't get queue");

	VkQueue queue;
	vkGetDeviceQueue(m_ctxt.logicalDevice, m_deviceQueues[m_presentationQueueIndex].familyIndex, static_cast<uint32_t>(m_deviceQueues[m_presentationQueueIndex].queues.size()), &queue);
	m_deviceQueues[m_presentationQueueIndex].queues.emplace_back(queue);
	m_deviceQueues[m_presentationQueueIndex].available--;
	return queue;

}
#pragma endregion



#pragma region image
#pragma endregion

#pragma region buffer
#pragma endregion