#include "pch.h"
#include <fstream>
#include "VulkanDevice.h"
#include "VulkanSwapChain.h"

void VulkanDevice::createMemoryAllocator()
{
	VmaAllocatorCreateInfo vmaInfo
	{
		.flags,
		.physicalDevice,
		.device,
		.preferredLargeHeapBlockSize,
		.pAllocationCallbacks,
		.pDeviceMemoryCallbacks,
		.pHeapSizeLimit,
		.pVulkanFunctions,
		.instance,
		.vulkanApiVersion
	};
	////todo
	//vmaCreateAllocator(&vmaInfo, &m_memAllocator);
}

VulkanDevice::VulkanDevice(const VulkanDeviceContext& a_context) : VulkanObject<VulkanDeviceContext>{ a_context }, 
m_deviceCapabilities{ static_cast<uint32_t>(a_context.deviceIndex), a_context.physicalDevice }
{
	createMemoryAllocator();
}

VulkanDevice::VulkanDevice(VulkanDeviceContext&& a_context) noexcept : VulkanObject<VulkanDeviceContext>{ a_context },
m_deviceCapabilities{ static_cast<uint32_t>(a_context.deviceIndex), a_context.physicalDevice }
{
	createMemoryAllocator();
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

#pragma region command
void VulkanDevice::createCommandBuffers(const QueueFlag a_flag)
{
	if (auto iter = m_deviceQueues.find(a_flag); iter != m_deviceQueues.cend() && iter->second.m_commandPool == VK_NULL_HANDLE)
	{
		// All command buffers are allocated from a command pool
		VkCommandPoolCreateInfo commandPoolCI = Vulkan::Initializers::commandPoolCreateInfo(VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT, iter->second.familyIndex);
		VK_CHECK_EXCEPT(vkCreateCommandPool(m_ctxt.logicalDevice, &commandPoolCI, nullptr, &iter->second.m_commandPool))

		// Allocate one command buffer per max. concurrent frame from above pool
		VkCommandBufferAllocateInfo cmdBufAllocateInfo = Vulkan::Initializers::commandBufferCreateInfo(iter->second.m_commandPool, VK_COMMAND_BUFFER_LEVEL_PRIMARY, VulkanDevice::MAX_FRAME);
		VK_CHECK_EXCEPT(vkAllocateCommandBuffers(m_ctxt.logicalDevice, &cmdBufAllocateInfo, iter->second.commandBuffers.data()))
	}
}

VkQueue VulkanDevice::createQueue(const QueueFlag a_flag)
{
	if (auto iter = m_deviceQueues.find(a_flag); iter != m_deviceQueues.cend())
	{
		VkQueue queue;
		vkGetDeviceQueue(m_ctxt.logicalDevice, iter->second.familyIndex, static_cast<uint32_t>(iter->second.queues.size()), &queue);
		iter->second.queues.emplace_back(queue);
		return queue;
	}
	throw Exception("Can't get queue");
}
#pragma endregion

#pragma region shader
VkShaderModule VulkanDevice::loadSPIRVShader(const std::string& a_filename)const
{
	VkShaderModule shaderModule = VK_NULL_HANDLE;	
	if (std::ifstream fileStream(a_filename, std::ios::binary | std::ios::in | std::ios::ate); fileStream.is_open())
	{
		const size_t fileSize = fileStream.tellg();
		fileStream.seekg(0, std::ios::beg);

		if (fileSize > 0)
		{
			std::vector<char> fileData(fileSize);
			fileStream.read(fileData.data(), fileSize);
			fileStream.close();

			// Create a new shader module that will be used for pipeline creation
			VkShaderModuleCreateInfo shaderModuleCI = Vulkan::Initializers::shaderModuleCreateInfo(fileData);
			VK_CHECK_EXCEPT(vkCreateShaderModule(m_ctxt.logicalDevice, &shaderModuleCI, nullptr, &shaderModule))

		}

	}
	return shaderModule;
}
#pragma endregion

#pragma region image
#pragma endregion

#pragma region buffer
#pragma endregion