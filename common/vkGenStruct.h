#pragma once
/***********************************************
* @headerfile vk_initializers.h
* @date 20 / 04 / 2024
* @author Roomain
************************************************/
#include <vulkan/vulkan.hpp>

/*@brief initialize structure of application*/
[[nodiscard]] constexpr VkApplicationInfo gen_applicationInfo()
{
	return VkApplicationInfo{ .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO, .pNext = nullptr, .applicationVersion = 1, .engineVersion = 1, .apiVersion = VK_API_VERSION_1_3 };
}

/*@brief initialize structure of instance*/
[[nodiscard]] constexpr VkInstanceCreateInfo gen_instanceCreateInfo()
{
	return VkInstanceCreateInfo{ .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, .pNext = nullptr, .flags = 0 };
}

/*@brief initialize debug callback create info*/
[[nodiscard]] constexpr VkDebugReportCallbackCreateInfoEXT gen_debugCallbackCreateInfo()
{
	return VkDebugReportCallbackCreateInfoEXT{ .sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT };
}

/*@brief initialize debug callback create info*/
[[nodiscard]] constexpr VkDebugUtilsMessengerCreateInfoEXT gen_messageCallbackCreateInfo()
{
	return VkDebugUtilsMessengerCreateInfoEXT{ .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT, .pNext = nullptr , .pUserData = nullptr };
}

/*@brief initialize create device*/
[[nodiscard]] constexpr VkDeviceCreateInfo gen_deviceCreateInfo()
{
	return VkDeviceCreateInfo{ .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO, .pNext = nullptr };
}

/*@brief initialize create device*/
[[nodiscard]] constexpr VkDeviceQueueCreateInfo gen_queueCreateInfo()
{
	return VkDeviceQueueCreateInfo{ .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO, .pNext = nullptr };
}

/*@brief initialize create device*/
[[nodiscard]] constexpr VkCommandPoolCreateInfo gen_cmdPoolCreateInfo()
{
	return VkCommandPoolCreateInfo{ .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO, .pNext = nullptr };
}


[[nodiscard]] constexpr VkSwapchainCreateInfoKHR gen_swapChainCreateInfo()
{
	return VkSwapchainCreateInfoKHR{ .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR, .pNext = nullptr };
}

[[nodiscard]] constexpr VkImageViewCreateInfo gen_imageViewCreateInfo(const VkFormat a_colorFormat, const VkImage a_image)
{
	return VkImageViewCreateInfo{
		.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.image = a_image,
		.viewType = VK_IMAGE_VIEW_TYPE_2D,
		.format = a_colorFormat,
		.components = {
			VK_COMPONENT_SWIZZLE_R,
			VK_COMPONENT_SWIZZLE_G,
			VK_COMPONENT_SWIZZLE_B,
			VK_COMPONENT_SWIZZLE_A
		},
		.subresourceRange {.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
		.baseMipLevel = 0,
		.levelCount = 1,
		.baseArrayLayer = 0,
		.layerCount = 1
		}
	};
}

[[nodiscard]] constexpr VkPresentInfoKHR gen_presentInfo()
{
	return VkPresentInfoKHR{
		.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
		.pNext = nullptr
	};
}

[[nodiscard]] constexpr VkCommandBufferAllocateInfo gen_allocCmdBufferInfo(const VkCommandPool a_commandPool, const VkCommandBufferLevel a_level, const uint32_t a_bufferCount)
{
	return VkCommandBufferAllocateInfo{
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
		.pNext = nullptr,
		.commandPool = a_commandPool,
		.level = a_level,
		.commandBufferCount = a_bufferCount
	};
}

/*@brief initialize create device*/
[[nodiscard]] constexpr VkPhysicalDeviceFeatures gen_physicalFeatures()
{
	return VkPhysicalDeviceFeatures{
	.robustBufferAccess = false,
	.fullDrawIndexUint32 = false,
	.imageCubeArray = false,
	.independentBlend = false,
	.geometryShader = false,
	.tessellationShader = false,
	.sampleRateShading = false,
	.dualSrcBlend = false,
	.logicOp = false,
	.multiDrawIndirect = false,
	.drawIndirectFirstInstance = false,
	.depthClamp = false,
	.depthBiasClamp = false,
	.fillModeNonSolid = false,
	.depthBounds = false,
	.wideLines = false,
	.largePoints = false,
	.alphaToOne = false,
	.multiViewport = false,
	.samplerAnisotropy = false,
	.textureCompressionETC2 = false,
	.textureCompressionASTC_LDR = false,
	.textureCompressionBC = false,
	.occlusionQueryPrecise = false,
	.pipelineStatisticsQuery = false,
	.vertexPipelineStoresAndAtomics = false,
	.fragmentStoresAndAtomics = false,
	.shaderTessellationAndGeometryPointSize = false,
	.shaderImageGatherExtended = false,
	.shaderStorageImageExtendedFormats = false,
	.shaderStorageImageMultisample = false,
	.shaderStorageImageReadWithoutFormat = false,
	.shaderStorageImageWriteWithoutFormat = false,
	.shaderUniformBufferArrayDynamicIndexing = false,
	.shaderSampledImageArrayDynamicIndexing = false,
	.shaderStorageBufferArrayDynamicIndexing = false,
	.shaderStorageImageArrayDynamicIndexing = false,
	.shaderClipDistance = false,
	.shaderCullDistance = false,
	.shaderFloat64 = false,
	.shaderInt64 = false,
	.shaderInt16 = false,
	.shaderResourceResidency = false,
	.shaderResourceMinLod = false,
	.sparseBinding = false,
	.sparseResidencyBuffer = false,
	.sparseResidencyImage2D = false,
	.sparseResidencyImage3D = false,
	.sparseResidency2Samples = false,
	.sparseResidency4Samples = false,
	.sparseResidency8Samples = false,
	.sparseResidency16Samples = false,
	.sparseResidencyAliased = false,
	.variableMultisampleRate = false,
	.inheritedQueries = false
	};
}

[[nodiscard]] constexpr VkFenceCreateInfo gen_fence(const VkFenceCreateFlags a_flags)
{
	return VkFenceCreateInfo{.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO, .pNext = nullptr, .flags = a_flags };
}

[[nodiscard]] constexpr  VkSemaphoreCreateInfo gen_semaphore(const VkEventCreateFlags a_flag)
{
	return VkSemaphoreCreateInfo{ .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO, .pNext = nullptr, .flags = a_flag};
}

[[nodiscard]] constexpr VkFramebufferCreateInfo gen_FrameBuffer()
{
	return VkFramebufferCreateInfo{ .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO, .pNext = nullptr };
}