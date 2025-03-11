#pragma once
/***********************************************
* @headerfile VulkanInitializers.h
* @date 24 / 08 / 2024
* @author Roomain
************************************************/
#include "vulkan/vulkan.h"
#include <utility>
#include <vector>
#include "common/string_utils.h"

/*@brief functions for structure initialisation*/
namespace Vulkan::Initializers
{

	[[nodiscard]] constexpr VkViewport viewport(const float a_x, const float a_y, const float a_width, const float a_height, const float a_near, const float a_far)
	{
		return VkViewport{ a_x, a_y, a_width, a_height, a_near, a_far };
	}

	[[nodiscard]] constexpr VkExtent2D extent2D(const uint32_t a_width, const uint32_t a_height)
	{
		return VkExtent2D{ a_width, a_height };
	}

	[[nodiscard]] constexpr VkOffset2D offset2D(const int32_t a_x, const int32_t a_y)
	{
		return VkOffset2D{ a_x, a_y };
	}

	[[nodiscard]] constexpr VkExtent3D extent3D(const uint32_t a_width, const uint32_t a_height, const uint32_t a_depth)
	{
		return VkExtent3D{ a_width, a_height, a_depth };
	}

	[[nodiscard]] constexpr VkOffset3D offset3D(const int32_t a_x, const int32_t a_y, const int32_t a_z)
	{
		return VkOffset3D{ a_x, a_y, a_z };
	}

	[[nodiscard]] constexpr VkRect2D rect2D(const int32_t a_x, const int32_t a_y, const uint32_t a_width, const uint32_t a_height)
	{
		return VkRect2D{ offset2D(a_x, a_y), extent2D(a_width, a_height) };
	}
	
	[[nodiscard]] constexpr VkDebugReportCallbackCreateInfoEXT debugCallbackCreateInfo()
	{
		return VkDebugReportCallbackCreateInfoEXT{ .sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT };
	}

	[[nodiscard]] constexpr VkDebugUtilsMessengerCreateInfoEXT messageCallbackCreateInfo()
	{
		return VkDebugUtilsMessengerCreateInfoEXT{ .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT, 
			.pNext = nullptr ,
			.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
			.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
			.pUserData = nullptr 
		};
	}

	[[nodiscard]] constexpr VkApplicationInfo applicationInfo(const char* a_appName, const uint32_t a_appVersion, 
		const char* a_engineName, const uint32_t a_engineVersion, const uint32_t a_apiVersion)
	{
		return VkApplicationInfo{ 
			.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO, 
			.pNext = nullptr,
			.pApplicationName = a_appName,
			.applicationVersion = a_appVersion,
			.pEngineName = a_engineName,
			.engineVersion = a_engineVersion,
			.apiVersion = a_apiVersion
		};
	}

	[[nodiscard]] constexpr VkInstanceCreateInfo instanceCreateInfo(
		const VkApplicationInfo* a_appInfo,
		const std::vector<std::string>& a_extensions,
		const std::vector<std::string>& a_layers)
	{
		return VkInstanceCreateInfo{ 
			.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, 
			.pNext = nullptr, 
			.flags = 0,
			.pApplicationInfo = a_appInfo,
			.enabledLayerCount = static_cast<uint32_t>(a_extensions.size()),
			.ppEnabledLayerNames =  vStringToChar(a_extensions).data(),
			.enabledExtensionCount = static_cast<uint32_t>(a_layers.size()),
			.ppEnabledExtensionNames =  vStringToChar(a_layers).data()
		 };
	}

	[[nodiscard]] inline VkDeviceCreateInfo deviceCreateInfo(const std::vector<VkDeviceQueueCreateInfo>& a_queueInfo,
		const std::vector<std::string>& a_extensions,
		const std::vector<std::string>& a_layers,
		const VkPhysicalDeviceFeatures* a_features,
		const VkDeviceCreateFlags a_flags)
	{
		return VkDeviceCreateInfo{ 
			.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO, 
			.pNext = nullptr,
			.flags = a_flags,
			.queueCreateInfoCount = static_cast<uint32_t>(a_queueInfo.size()),
			.pQueueCreateInfos = a_queueInfo.data(),
			.enabledLayerCount = static_cast<uint32_t>(a_layers.size()),
			.ppEnabledLayerNames = vStringToChar(a_layers).data(),
			.enabledExtensionCount = static_cast<uint32_t>(a_extensions.size()),
			.ppEnabledExtensionNames = vStringToChar(a_extensions).data(),
			.pEnabledFeatures = a_features
		};
	}

	[[nodiscard]] constexpr VkDeviceQueueCreateInfo queueCreateInfo(const uint32_t a_familyIndex,
		const uint32_t a_queueCount,
		const std::vector<float>& a_priorities,
		const VkDeviceQueueCreateFlags a_flag = 0)
	{
		return VkDeviceQueueCreateInfo{ 
			.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
    		.pNext = nullptr,
    		.flags = a_flag,
    		.queueFamilyIndex = a_familyIndex,
    		.queueCount = a_queueCount,
    		.pQueuePriorities = a_priorities.data()
			};
	}

	[[nodiscard]] constexpr VkFramebufferCreateInfo frameBufferCreateInfo(const VkRenderPass a_renderPass, 
	const std::vector<VkImageView>& a_attachment, const uint32_t a_Width, const uint32_t a_Height)
	{
		return VkFramebufferCreateInfo{ 
			.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO, 
			.pNext = nullptr, 
			.renderPass = a_renderPass,
			.attachmentCount = static_cast<uint32_t>(a_attachment.size()),
			.pAttachments = a_attachment.data(),
			.width = a_Width,
			.height = a_Height,
			.layers = 1
		 };
	}


	[[nodiscard]] constexpr VkSwapchainCreateInfoKHR swapChainCreateInfoKHR(const VkSurfaceKHR a_surface, 
		const VkSurfaceFormatKHR& a_format, 
		const uint32_t a_imageCount,
		const VkExtent2D& a_extent,
		const VkImageUsageFlags a_usage,
		const VkSurfaceTransformFlagBitsKHR a_transform,
		const VkCompositeAlphaFlagBitsKHR a_compositeFlag,
		const VkPresentModeKHR a_presentMode,
		const VkBool32 a_clipped,
		VkSwapchainKHR a_oldSwapChain = VK_NULL_HANDLE
		)
	{
		return VkSwapchainCreateInfoKHR{ .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR, 
			.pNext = nullptr, 
			.flags = 0, 
			.surface = a_surface, 
			.minImageCount = a_imageCount,
			.imageFormat = a_format.format, 
			.imageColorSpace = a_format.colorSpace, 
			.imageExtent = a_extent,
			.imageArrayLayers = 1,
			.imageUsage = a_usage,
			.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,	// no sharing
			.queueFamilyIndexCount = 0,						// number of shared queues
			.pQueueFamilyIndices = nullptr,					// shared queues
			.preTransform = a_transform,
			.compositeAlpha = a_compositeFlag,
			.presentMode = a_presentMode,
			.clipped = a_clipped,
			.oldSwapchain = a_oldSwapChain
		};
	}

	
	[[nodiscard]] constexpr VkMemoryAllocateInfo memoryAllocateInfo(const VkDeviceSize& a_allocSize, const uint32_t a_memType)
	{
		return VkMemoryAllocateInfo{ 
			.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO, 
			.pNext = nullptr, 
			.allocationSize = a_allocSize,
			.memoryTypeIndex =  a_memType
		};
	}

	[[nodiscard]] constexpr VkCommandBufferAllocateInfo commandBufferCreateInfo(const VkCommandPool a_cmdPool, 
	const VkCommandBufferLevel a_level, uint32_t a_bufferCount)
	{
		return VkCommandBufferAllocateInfo{ 
			.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO, 
			.pNext = nullptr, 
			.commandPool = a_cmdPool, 
			.level = a_level, 
			.commandBufferCount = a_bufferCount 
		};
	}

	[[nodiscard]] constexpr VkCommandPoolCreateInfo commandPoolCreateInfo(const VkCommandPoolCreateFlags a_flags, 
	const uint32_t a_familyIndex)
	{
		return VkCommandPoolCreateInfo{ 
			.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO, 
			.pNext = nullptr, 
			.flags = a_flags, .
			queueFamilyIndex = a_familyIndex 
		};
	}

	[[nodiscard]] constexpr VkCommandBufferBeginInfo commandBufferBeginInfo(const VkCommandBufferUsageFlags a_flags, 
	const VkCommandBufferInheritanceInfo* a_pBuffInheritInfo)
	{
		return VkCommandBufferBeginInfo{ 
			.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO, 
			.pNext = nullptr, 
			.flags = a_flags, 
			.pInheritanceInfo = a_pBuffInheritInfo 
		};
	}

	[[nodiscard]] inline VkImageViewCreateInfo imageViewCreateInfo(const VkFormat a_colorFormat,
		const VkImage a_image, 
		const VkImageViewType a_viewType,
		const VkImageViewCreateFlags a_flag,
		const VkImageSubresourceRange& a_subResource
		)
	{
		return VkImageViewCreateInfo{ 
			.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO, 
			.pNext = nullptr,
			.flags = a_flag,
    		.image = a_image,
    		.viewType = a_viewType,
    		.format = a_colorFormat,
    		.components = {
				VK_COMPONENT_SWIZZLE_R,
				VK_COMPONENT_SWIZZLE_G,
				VK_COMPONENT_SWIZZLE_B,
				VK_COMPONENT_SWIZZLE_A
			},
    		.subresourceRange = a_subResource
		};
	}

	[[nodiscard]] constexpr VkBufferViewCreateInfo bufferViewCreateInfo(const VkBufferViewCreateFlags a_flag, 
		const VkBuffer a_bufferHandle, 
		const VkFormat a_format, 
		const VkDeviceSize& a_offset, 
		const VkDeviceSize& a_range)
	{
		return VkBufferViewCreateInfo{ 
			.sType = VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO, 
			.pNext = nullptr, 
			.flags = a_flag, 
			.buffer = a_bufferHandle, 
			.format = a_format, 
			.offset = a_offset, 
			.range = a_range 
		};
	}

	[[nodiscard]] constexpr VkImageCreateInfo imageCreateInfo()
	{
		return VkImageCreateInfo{ 
			.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO, 
			.pNext = nullptr, 
			.imageType = VK_IMAGE_TYPE_2D 
		};
	}

	[[nodiscard]] constexpr VkSubmitInfo submitInfo(const std::vector<VkSemaphore>& a_waitSemaphore,
		const std::vector<VkPipelineStageFlags>& a_pipelineStages,
		const std::vector<VkCommandBuffer>& a_cmdBuffers,
		const std::vector<VkSemaphore>& a_signalSemaphore
	)
	{
		return VkSubmitInfo{ 
			.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO, 
			.pNext = nullptr,
    		.waitSemaphoreCount = static_cast<uint32_t>(a_waitSemaphore.size()),
    		.pWaitSemaphores = a_waitSemaphore.data(),
    		.pWaitDstStageMask = a_pipelineStages.data(),
    		.commandBufferCount = static_cast<uint32_t>(a_cmdBuffers.size()),
    		.pCommandBuffers = a_cmdBuffers.data(),
    		.signalSemaphoreCount = static_cast<uint32_t>(a_signalSemaphore.size()),
    		.pSignalSemaphores = a_signalSemaphore.data(),
		};
	}

	[[nodiscard]] constexpr VkSubmitInfo submitInfo(const VkSemaphore* a_waitSemaphore,
		const std::vector<VkPipelineStageFlags>& a_pipelineStages,
		const VkCommandBuffer* a_cmdBuffers,
		const VkSemaphore* a_signalSemaphore,
		const uint32_t a_waitCount = 1,
		const uint32_t a_bufferCount = 1,
		const uint32_t a_signalCount = 1
	)
	{
		return VkSubmitInfo{ 
			.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO, 
			.pNext = nullptr,
    		.waitSemaphoreCount = a_waitCount,
    		.pWaitSemaphores = a_waitSemaphore,
    		.pWaitDstStageMask = a_pipelineStages.data(),
    		.commandBufferCount = a_bufferCount,
    		.pCommandBuffers = a_cmdBuffers,
    		.signalSemaphoreCount = a_signalCount,
    		.pSignalSemaphores = a_signalSemaphore,
		};
	}

	[[nodiscard]] constexpr VkBufferCreateInfo bufferCreateInfo(const VkBufferCreateFlags a_flag,
	const VkDeviceSize& a_size,
	const VkBufferUsageFlags a_usage,
	const VkSharingMode& a_shareMode,
	const std::vector<uint32_t>& a_familyIndicies)
	{
		return VkBufferCreateInfo{ 
			.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO, 
			.pNext = nullptr, 
			.flags = a_flag,
			.size = a_size,
			.usage = a_usage,
			.sharingMode = a_shareMode,
			.queueFamilyIndexCount = static_cast<uint32_t>(a_familyIndicies.size()), 
			.pQueueFamilyIndices = a_familyIndicies.data() 
			};
	}

	[[nodiscard]] constexpr VkBufferCreateInfo bufferCreateInfo(const VkBufferCreateFlags a_flag,
	const VkDeviceSize& a_size,
	const VkBufferUsageFlags a_usage,
	const VkSharingMode& a_shareMode,
	const uint32_t* a_familyIndex)
	{
		return VkBufferCreateInfo{ 
			.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO, 
			.pNext = nullptr, 
			.flags = a_flag,
			.size = a_size,
			.usage = a_usage,
			.sharingMode = a_shareMode,
			.queueFamilyIndexCount = 1, 
			.pQueueFamilyIndices = a_familyIndex
			};
	}

	[[nodiscard]] constexpr VkDescriptorSetLayoutBinding descriptorSetLayoutBinding(
		VkDescriptorType a_type,
		VkShaderStageFlags a_stageFlags,
		uint32_t a_binding,
		uint32_t a_descriptorCount = 1)
	{
		return VkDescriptorSetLayoutBinding{ .binding = a_binding, .descriptorType = a_type,  .descriptorCount = a_descriptorCount, .stageFlags = a_stageFlags };
	}

	[[nodiscard]] constexpr VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo(
		const VkDescriptorSetLayoutBinding* a_pBindings,
		uint32_t a_bindingCount)
	{
		return VkDescriptorSetLayoutCreateInfo{
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
		.pNext = nullptr,
		.bindingCount = a_bindingCount,
		.pBindings = a_pBindings };
	}

	[[nodiscard]] constexpr VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo(
		const std::vector<VkDescriptorSetLayoutBinding>& a_bindings)
	{
		return VkDescriptorSetLayoutCreateInfo{
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
		.pNext = nullptr,
		.bindingCount = static_cast<uint32_t>(a_bindings.size()),
		.pBindings = a_bindings.data() };
	}

	[[nodiscard]] constexpr VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo(
		const VkDescriptorSetLayout* a_pSetLayouts,
		uint32_t a_setLayoutCount = 1)
	{
		return VkPipelineLayoutCreateInfo{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
		.pNext = nullptr,
		.setLayoutCount = a_setLayoutCount,
		.pSetLayouts = a_pSetLayouts };
	}

	[[nodiscard]] constexpr VkPipelineShaderStageCreateInfo pipelineShaderStageCreateInfo(
		const VkShaderStageFlagBits a_stage, const VkShaderModule a_shaderModule)
	{
		return VkPipelineShaderStageCreateInfo{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.stage = a_stage,
		.module = a_shaderModule,
		.pName = "main"
		};
	}

	[[nodiscard]] constexpr VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo(
		uint32_t a_setLayoutCount = 1)
	{
		return VkPipelineLayoutCreateInfo{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
		.pNext = nullptr,
		.setLayoutCount = a_setLayoutCount };
	}

	[[nodiscard]] constexpr VkDescriptorSetAllocateInfo descriptorSetAllocateInfo(
		VkDescriptorPool a_descriptorPool,
		const VkDescriptorSetLayout* a_pSetLayouts,
		uint32_t a_descriptorSetCount)
	{
		return VkDescriptorSetAllocateInfo{
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
		.pNext = nullptr,
		.descriptorPool = a_descriptorPool,
		.descriptorSetCount = a_descriptorSetCount,
		.pSetLayouts = a_pSetLayouts };
	}


	[[nodiscard]] constexpr VkDescriptorImageInfo descriptorImageInfo(VkSampler a_sampler, VkImageView a_imageView, VkImageLayout a_imageLayout)
	{
		return VkDescriptorImageInfo{
		.sampler = a_sampler,
		.imageView = a_imageView,
		.imageLayout = a_imageLayout };
	}

	[[nodiscard]] inline VkShaderModuleCreateInfo shaderModuleCreateInfo(std::vector<char>& a_shaderCode)
	{
		return VkShaderModuleCreateInfo{
		.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
		.pNext = nullptr,
		.codeSize = a_shaderCode.size(),
		.pCode = reinterpret_cast<uint32_t*>(a_shaderCode.data()) };
	}

	[[nodiscard]] constexpr VkWriteDescriptorSet writeDescriptorSet(
		VkDescriptorSet a_dstSet,
		VkDescriptorType a_type,
		uint32_t a_binding,
		VkDescriptorBufferInfo* a_bufferInfo,
		uint32_t a_descriptorCount = 1)
	{
		return VkWriteDescriptorSet{
		.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
		.pNext = nullptr,
		.dstSet = a_dstSet,
		.dstBinding = a_binding,
		.descriptorCount = a_descriptorCount,
		.descriptorType = a_type,
		.pBufferInfo = a_bufferInfo };
	}

	[[nodiscard]] constexpr VkWriteDescriptorSet writeDescriptorSet(
		VkDescriptorSet a_dstSet,
		VkDescriptorType a_type,
		uint32_t a_binding,
		VkDescriptorImageInfo* a_imageInfo,
		uint32_t a_descriptorCount = 1)
	{
		return VkWriteDescriptorSet{
		.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
		.pNext = nullptr,
		.dstSet = a_dstSet,
		.dstBinding = a_binding,
		.descriptorCount = a_descriptorCount,
		.descriptorType = a_type,
		.pImageInfo = a_imageInfo };
	}

	[[nodiscard]] constexpr VkVertexInputBindingDescription vertexInputBindingDescription(
		uint32_t a_binding,
		uint32_t a_stride,
		VkVertexInputRate a_inputRate)
	{
		return VkVertexInputBindingDescription{
		.binding = a_binding,
		.stride = a_stride,
		.inputRate = a_inputRate };
	}

	[[nodiscard]] constexpr VkVertexInputAttributeDescription vertexInputAttributeDescription(
		uint32_t a_binding,
		uint32_t a_location,
		VkFormat a_format,
		uint32_t a_offset)
	{
		return VkVertexInputAttributeDescription{
		.location = a_location,
		.binding = a_binding,
		.format = a_format,
		.offset = a_offset };
	}

	[[nodiscard]] constexpr VkPipelineVertexInputStateCreateInfo pipelineVertexInputStateCreateInfo()
	{
		return VkPipelineVertexInputStateCreateInfo{ .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO, .pNext = nullptr };
	}

	[[nodiscard]] constexpr VkPipelineVertexInputStateCreateInfo pipelineVertexInputStateCreateInfo(
		const std::vector<VkVertexInputBindingDescription>& a_vertexBindingDescriptions,
		const std::vector<VkVertexInputAttributeDescription>& a_vertexAttributeDescriptions
	)
	{
		return VkPipelineVertexInputStateCreateInfo{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
		.pNext = nullptr,
		.vertexBindingDescriptionCount = static_cast<uint32_t>(a_vertexBindingDescriptions.size()),
		.pVertexBindingDescriptions = a_vertexBindingDescriptions.data(),
		.vertexAttributeDescriptionCount = static_cast<uint32_t>(a_vertexAttributeDescriptions.size()),
		.pVertexAttributeDescriptions = a_vertexAttributeDescriptions.data() };
	}

	[[nodiscard]] constexpr VkPipelineInputAssemblyStateCreateInfo pipelineInputAssemblyStateCreateInfo(
		VkPrimitiveTopology a_topology,
		VkPipelineInputAssemblyStateCreateFlags a_flags,
		VkBool32 a_primitiveRestartEnable)
	{
		return VkPipelineInputAssemblyStateCreateInfo{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = a_flags,
		.topology = a_topology,
		.primitiveRestartEnable = a_primitiveRestartEnable };
	}

	[[nodiscard]] constexpr VkPipelineRasterizationStateCreateInfo pipelineRasterizationStateCreateInfo(
		VkPolygonMode a_polygonMode,
		VkCullModeFlags a_cullMode,
		VkFrontFace a_frontFace,
		VkPipelineRasterizationStateCreateFlags a_flags = 0)
	{
		return VkPipelineRasterizationStateCreateInfo{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = a_flags,
		.depthClampEnable = VK_FALSE,
		.polygonMode = a_polygonMode,
		.cullMode = a_cullMode,
		.frontFace = a_frontFace,
		.lineWidth = 1.0f };
	}

	[[nodiscard]] constexpr VkPipelineColorBlendAttachmentState pipelineColorBlendAttachmentState(
		VkColorComponentFlags a_colorWriteMask,
		VkBool32 a_blendEnable)
	{
		return VkPipelineColorBlendAttachmentState{
		.blendEnable = a_blendEnable,
		.colorWriteMask = a_colorWriteMask };
	}

	[[nodiscard]] constexpr VkPipelineColorBlendStateCreateInfo pipelineColorBlendStateCreateInfo(
		uint32_t a_attachmentCount,
		const VkPipelineColorBlendAttachmentState* a_pAttachments)
	{
		return VkPipelineColorBlendStateCreateInfo{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
		.pNext = nullptr,
		.attachmentCount = a_attachmentCount,
		.pAttachments = a_pAttachments };
	}

	[[nodiscard]] constexpr VkPipelineDepthStencilStateCreateInfo pipelineDepthStencilStateCreateInfo(
		VkBool32 a_depthTestEnable,
		VkBool32 a_depthWriteEnable,
		VkCompareOp a_depthCompareOp)
	{
		return VkPipelineDepthStencilStateCreateInfo{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
		.pNext = nullptr,
		.depthTestEnable = a_depthTestEnable,
		.depthWriteEnable = a_depthWriteEnable,
		.depthCompareOp = a_depthCompareOp,
		.back{.compareOp = VK_COMPARE_OP_ALWAYS} };
	}

	[[nodiscard]] constexpr VkPipelineViewportStateCreateInfo pipelineViewportStateCreateInfo(
		uint32_t a_viewportCount,
		uint32_t a_scissorCount,
		VkPipelineViewportStateCreateFlags a_flags = 0)
	{
		return VkPipelineViewportStateCreateInfo{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = a_flags,
		.viewportCount = a_viewportCount,
		.scissorCount = a_scissorCount };
	}

	[[nodiscard]] constexpr VkPipelineMultisampleStateCreateInfo pipelineMultisampleStateCreateInfo(
		VkSampleCountFlagBits a_rasterizationSamples,
		VkPipelineMultisampleStateCreateFlags a_flags = 0)
	{
		return VkPipelineMultisampleStateCreateInfo{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = a_flags,
		.rasterizationSamples = a_rasterizationSamples };
	}

	[[nodiscard]] constexpr VkPipelineDynamicStateCreateInfo pipelineDynamicStateCreateInfo(
		const VkDynamicState* a_pDynamicStates,
		uint32_t a_dynamicStateCount,
		VkPipelineDynamicStateCreateFlags a_flags = 0)
	{
		return VkPipelineDynamicStateCreateInfo{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = a_flags,
		.dynamicStateCount = a_dynamicStateCount,
		.pDynamicStates = a_pDynamicStates };
	}

	[[nodiscard]] constexpr VkPipelineDynamicStateCreateInfo pipelineDynamicStateCreateInfo(
		const std::vector<VkDynamicState>& a_pDynamicStates,
		VkPipelineDynamicStateCreateFlags a_flags = 0)
	{
		return VkPipelineDynamicStateCreateInfo{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = a_flags,
		.dynamicStateCount = static_cast<uint32_t>(a_pDynamicStates.size()),
		.pDynamicStates = a_pDynamicStates.data() };
	}

	[[nodiscard]] constexpr VkPipelineTessellationStateCreateInfo pipelineTessellationStateCreateInfo(uint32_t a_patchControlPoints)
	{
		return VkPipelineTessellationStateCreateInfo{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO,
		.pNext = nullptr,
		.patchControlPoints = a_patchControlPoints };
	}


	[[nodiscard]] constexpr VkGraphicsPipelineCreateInfo graphicPipelineCreateInfo(
		const VkPipelineCreateFlags a_flags,
		const std::vector<VkPipelineShaderStageCreateInfo>& a_shaderStages,
		const VkPipelineVertexInputStateCreateInfo* a_pVertexInputState,
		const VkPipelineInputAssemblyStateCreateInfo* a_pInputAssemblyState,
		const VkPipelineTessellationStateCreateInfo* a_pTessellationState,
		const VkPipelineViewportStateCreateInfo* a_pViewportState,
		const VkPipelineRasterizationStateCreateInfo* a_pRasterizationState,
		const VkPipelineMultisampleStateCreateInfo* a_pMultisampleState,
		const VkPipelineDepthStencilStateCreateInfo* a_pDepthStencilState,
		const VkPipelineColorBlendStateCreateInfo* a_pColorBlendState,
		const VkPipelineDynamicStateCreateInfo* a_pDynamicState,
		VkPipelineLayout a_layout,
		VkRenderPass     a_renderPass,
		uint32_t         a_subpass,
		VkPipeline       a_basePipelineHandle = VK_NULL_HANDLE,
		int32_t          a_basePipelineIndex = -1)
	{
		return VkGraphicsPipelineCreateInfo{
			.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
			.pNext = nullptr,
			.flags = a_flags,
			.stageCount = static_cast<uint32_t>(a_shaderStages.size()),
			.pStages = a_shaderStages.data(),
			.pVertexInputState = a_pVertexInputState,
			.pInputAssemblyState = a_pInputAssemblyState,
			.pTessellationState = a_pTessellationState,
			.pViewportState = a_pViewportState,
			.pRasterizationState = a_pRasterizationState,
			.pMultisampleState = a_pMultisampleState,
			.pDepthStencilState = a_pDepthStencilState,
			.pColorBlendState = a_pColorBlendState,
			.pDynamicState = a_pDynamicState,
			.layout = a_layout,
			.renderPass = a_renderPass,
			.subpass = a_subpass,
			.basePipelineHandle = a_basePipelineHandle,
			.basePipelineIndex = a_basePipelineIndex

		};
	}

	[[nodiscard]] constexpr VkComputePipelineCreateInfo computePipelineCreateInfo(
		VkPipelineLayout layout,
		VkPipelineCreateFlags flags = 0)
	{
		return VkComputePipelineCreateInfo{
		.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO,
		.pNext = nullptr,
		.flags = flags,
		.layout = layout };
	}

	[[nodiscard]] constexpr VkPushConstantRange pushConstantRange(
		VkShaderStageFlags a_stageFlags,
		uint32_t a_size,
		uint32_t a_offset)
	{
		return VkPushConstantRange{
		.stageFlags = a_stageFlags,
		.offset = a_offset,
		.size = a_size };
	}

	[[nodiscard]] constexpr VkBindSparseInfo bindSparseInfo()
	{
		return VkBindSparseInfo{ .sType = VK_STRUCTURE_TYPE_BIND_SPARSE_INFO, .pNext = nullptr };
	}

	/** @brief Initialize a map entry for a shader specialization constant */
	[[nodiscard]] constexpr VkSpecializationMapEntry specializationMapEntry(uint32_t a_constantID, uint32_t a_offset, size_t a_size)
	{
		return VkSpecializationMapEntry{
		.constantID = a_constantID,
		.offset = a_offset,
		.size = a_size };
	}

	/** @brief Initialize a specialization constant info structure to pass to a shader stage */
	[[nodiscard]] constexpr VkSpecializationInfo specializationInfo(uint32_t a_mapEntryCount,
		const VkSpecializationMapEntry* a_mapEntries, size_t a_dataSize, const void* a_data)
	{
		return VkSpecializationInfo{
		.mapEntryCount = a_mapEntryCount,
		.pMapEntries = a_mapEntries,
		.dataSize = a_dataSize,
		.pData = a_data };
	}

	/** @brief Initialize a specialization constant info structure to pass to a shader stage */
	[[nodiscard]] constexpr VkSpecializationInfo specializationInfo(const std::vector<VkSpecializationMapEntry>& a_mapEntries,
		size_t a_dataSize, const void* a_data)
	{
		return VkSpecializationInfo{
		.mapEntryCount = static_cast<uint32_t>(a_mapEntries.size()),
		.pMapEntries = a_mapEntries.data(),
		.dataSize = a_dataSize,
		.pData = a_data };
	}

	// Ray tracing related
	[[nodiscard]] constexpr VkAccelerationStructureGeometryKHR accelerationStructureGeometryKHR()
	{
		return VkAccelerationStructureGeometryKHR{
		.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
		.pNext = nullptr };
	}

	[[nodiscard]] constexpr VkAccelerationStructureBuildGeometryInfoKHR accelerationStructureBuildGeometryInfoKHR()
	{
		return VkAccelerationStructureBuildGeometryInfoKHR{
		.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
		.pNext = nullptr };
	}

	[[nodiscard]] constexpr VkAccelerationStructureBuildSizesInfoKHR accelerationStructureBuildSizesInfoKHR()
	{
		return VkAccelerationStructureBuildSizesInfoKHR{
		.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR,
		.pNext = nullptr };
	}

	[[nodiscard]] constexpr VkRayTracingShaderGroupCreateInfoKHR rayTracingShaderGroupCreateInfoKHR()
	{
		return VkRayTracingShaderGroupCreateInfoKHR{
		.sType = VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_KHR,
		.pNext = nullptr };
	}

	[[nodiscard]] constexpr VkRayTracingPipelineCreateInfoKHR rayTracingPipelineCreateInfoKHR()
	{
		return VkRayTracingPipelineCreateInfoKHR{
		.sType = VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_CREATE_INFO_KHR,
		.pNext = nullptr };
	}

	[[nodiscard]] constexpr VkWriteDescriptorSetAccelerationStructureKHR writeDescriptorSetAccelerationStructureKHR()
	{
		return VkWriteDescriptorSetAccelerationStructureKHR{
		.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_ACCELERATION_STRUCTURE_KHR,
		.pNext = nullptr };
	}

	[[nodiscard]] constexpr VkPresentInfoKHR presentationKHR(const uint32_t& a_semaphoreCount, VkSemaphore* a_pSemaphore, const uint32_t& a_swapChainCount, const VkSwapchainKHR* a_pSwapChain, const uint32_t* a_pImgIndices)
	{
		return VkPresentInfoKHR{
		.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
		.pNext = nullptr,
		.waitSemaphoreCount = a_semaphoreCount,
		.pWaitSemaphores = a_pSemaphore,
		.swapchainCount = a_swapChainCount,
		.pSwapchains = a_pSwapChain,
		.pImageIndices = a_pImgIndices,
		.pResults = nullptr };
	}

	[[nodiscard]] constexpr VkSemaphoreCreateInfo semaphoreCreateInfo(VkSemaphoreCreateFlags a_flags = 0)
	{
		return VkSemaphoreCreateInfo{ .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO, .pNext = nullptr, .flags = a_flags };
	}

	[[nodiscard]] constexpr VkFenceCreateInfo fenceCreateInfo(VkFenceCreateFlags a_flags = 0)
	{
		return VkFenceCreateInfo{ .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO, .pNext = nullptr, .flags = a_flags };
	}

	[[nodiscard]] constexpr VkFramebufferCreateInfo frameBufferCreateInfo(const std::vector<VkImageView>& a_attachment,
		const uint32_t a_width, const uint32_t a_height, const uint32_t a_layers, const VkFramebufferCreateFlags a_flags)
	{
		return VkFramebufferCreateInfo{ .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
			.pNext = nullptr,
			.flags = a_flags,
			.attachmentCount = static_cast<uint32_t>(a_attachment.size()),
			.pAttachments = a_attachment.data(),
			.width = a_width,
			.height = a_height,
			.layers = a_layers
		};
	}
}