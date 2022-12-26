#pragma once
#include "vulkan/vulkan.h"
#include <utility>

/*@brief functions for structure initialisation*/
namespace Vulkan::Initializers
{
	[[nodiscard]] constexpr VkViewport&& viewport(const float a_x, const float a_y, const float a_width, const float a_height, const float a_near, const float a_far)
	{
		return VkViewport{ a_x, a_y, a_width, a_height, a_near, a_far };
	}

	[[nodiscard]] constexpr VkExtent2D&& extent2D(const uint32_t a_width, const uint32_t a_height)
	{
		return VkExtent2D{ a_width, a_height };
	}

	[[nodiscard]] constexpr VkOffset2D offset2D(const int32_t a_x, const int32_t a_y)
	{
		return VkOffset2D{ a_x, a_y };
	}

	[[nodiscard]] constexpr VkExtent3D&& extent3D(const uint32_t a_width, const uint32_t a_height, const uint32_t a_depth)
	{
		return VkExtent3D{ a_width, a_height, a_depth };
	}

	[[nodiscard]] constexpr VkOffset3D offset3D(const int32_t a_x, const int32_t a_y, const int32_t a_z)
	{
		return VkOffset3D{ a_x, a_y, a_z };
	}
	
	[[nodiscard]] constexpr VkRect2D&& rect2D(const int32_t a_x, const int32_t a_y, const uint32_t a_width, const uint32_t a_height)
	{
		return VkRect2D{ std::move(offset2D(a_x, a_y)), std::move(extent2D(a_width, a_height))};
	}

	[[nodiscard]] constexpr VkApplicationInfo&& applicationInfo()
	{
		return std::move(VkApplicationInfo{ .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO, .pNext = nullptr });
	}

	[[nodiscard]] constexpr VkInstanceCreateInfo&& instanceCreateInfo()
	{
		return std::move(VkInstanceCreateInfo{ .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, .pNext = nullptr, .flags = 0 });
	}

	[[nodiscard]] constexpr VkDebugReportCallbackCreateInfoEXT&& debugCallbackCreateInfo()
	{
		return std::move(VkDebugReportCallbackCreateInfoEXT{ .sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT });
	}

	[[nodiscard]] constexpr VkDebugUtilsMessengerCreateInfoEXT&& messageCallbackCreateInfo()
	{
		return std::move(VkDebugUtilsMessengerCreateInfoEXT{ .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT, .pNext = nullptr , .pUserData = nullptr});
	}

	[[nodiscard]] constexpr VkDeviceCreateInfo&& deviceCreateInfo()
	{
		return std::move(VkDeviceCreateInfo{ .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO, .pNext = nullptr });
	}

	[[nodiscard]] constexpr VkDeviceQueueCreateInfo&& queueCreateInfo()
	{
		return std::move(VkDeviceQueueCreateInfo{ .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO });
	}

	[[nodiscard]] constexpr VkSwapchainCreateInfoKHR&& swapChainCreateInfoKHR()
	{
		return std::move(VkSwapchainCreateInfoKHR{ .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR });
	}

	[[nodiscard]] constexpr VkMemoryAllocateInfo&& memoryAllocateInfo()
	{
		return std::move(VkMemoryAllocateInfo{ .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO, .pNext = nullptr, .allocationSize = 0 });
	}
	
	[[nodiscard]] constexpr VkCommandBufferAllocateInfo&& commandBufferCreateInfo()
	{
		return std::move(VkCommandBufferAllocateInfo{ .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO, .pNext = nullptr });
	}

	[[nodiscard]] constexpr VkCommandBufferBeginInfo&& commandBufferBeginInfo()
	{
		return std::move(VkCommandBufferBeginInfo{ .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO, .pNext = nullptr });
	}

	[[nodiscard]] constexpr VkSubmitInfo&& dubmitInfo()
	{
		return std::move(VkSubmitInfo{ .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO, .pNext = nullptr });
	}

	[[nodiscard]] constexpr VkImageViewCreateInfo&& imageViewCreateInfo()
	{
		return std::move(VkImageViewCreateInfo{ .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO, .pNext = nullptr });
	}

	[[nodiscard]] constexpr VkImageCreateInfo&& imageCreateInfo()
	{
		return std::move(VkImageCreateInfo{ .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO, .pNext = nullptr, .imageType = VK_IMAGE_TYPE_2D });
	}

	[[nodiscard]] constexpr VkBufferCreateInfo&& bufferCreateInfo()
	{
		return std::move(VkBufferCreateInfo{ .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO, .pNext = nullptr, .queueFamilyIndexCount = 0, .pQueueFamilyIndices = nullptr });
	}

	[[nodiscard]] constexpr VkDescriptorSetLayoutBinding&& descriptorSetLayoutBinding(
		VkDescriptorType type,
		VkShaderStageFlags stageFlags,
		uint32_t binding,
		uint32_t descriptorCount = 1)
	{
		return VkDescriptorSetLayoutBinding{ .binding = binding, .descriptorType = type,  .descriptorCount = descriptorCount, .stageFlags = stageFlags };
	}

	[[nodiscard]] constexpr VkDescriptorSetLayoutCreateInfo&& descriptorSetLayoutCreateInfo(
		const VkDescriptorSetLayoutBinding* pBindings,
		uint32_t bindingCount)
	{
		return VkDescriptorSetLayoutCreateInfo{
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
		.pNext = nullptr,
		.bindingCount = bindingCount,
		.pBindings = pBindings};
	}

	[[nodiscard]] constexpr VkDescriptorSetLayoutCreateInfo&& descriptorSetLayoutCreateInfo(
		const std::vector<VkDescriptorSetLayoutBinding>& bindings)
	{
		return VkDescriptorSetLayoutCreateInfo{
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
		.pNext = nullptr,
		.bindingCount = static_cast<uint32_t>(bindings.size()),
		.pBindings = bindings.data() };
	}

	[[nodiscard]] constexpr VkPipelineLayoutCreateInfo&& pipelineLayoutCreateInfo(
		const VkDescriptorSetLayout* pSetLayouts,
		uint32_t setLayoutCount = 1)
	{
		return VkPipelineLayoutCreateInfo{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
		.pNext = nullptr,
		.setLayoutCount = setLayoutCount,
		.pSetLayouts = pSetLayouts };
	}

	[[nodiscard]] constexpr VkPipelineLayoutCreateInfo&& pipelineLayoutCreateInfo(
		uint32_t setLayoutCount = 1)
	{
		return VkPipelineLayoutCreateInfo{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
		.pNext = nullptr,
		.setLayoutCount = setLayoutCount };
	}

	[[nodiscard]] constexpr VkDescriptorSetAllocateInfo&& descriptorSetAllocateInfo(
		VkDescriptorPool descriptorPool,
		const VkDescriptorSetLayout* pSetLayouts,
		uint32_t descriptorSetCount)
	{
		return VkDescriptorSetAllocateInfo{
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
		.pNext = nullptr,
		.descriptorPool = descriptorPool,
		.descriptorSetCount = descriptorSetCount,
		.pSetLayouts = pSetLayouts };
	}

	[[nodiscard]] constexpr VkDescriptorImageInfo&& descriptorImageInfo(VkSampler sampler, VkImageView imageView, VkImageLayout imageLayout)
	{
		return VkDescriptorImageInfo{
		.sampler = sampler,
		.imageView = imageView,
		.imageLayout = imageLayout };
	}

	[[nodiscard]] constexpr VkWriteDescriptorSet&& writeDescriptorSet(
		VkDescriptorSet dstSet,
		VkDescriptorType type,
		uint32_t binding,
		VkDescriptorBufferInfo* bufferInfo,
		uint32_t descriptorCount = 1)
	{
		return VkWriteDescriptorSet{
		.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
		.pNext = nullptr,
		.dstSet = dstSet,
		.dstBinding = binding,
		.descriptorCount = descriptorCount,
		.descriptorType = type,
		.pBufferInfo = bufferInfo};
	}

	[[nodiscard]] constexpr VkWriteDescriptorSet&& writeDescriptorSet(
		VkDescriptorSet dstSet,
		VkDescriptorType type,
		uint32_t binding,
		VkDescriptorImageInfo* imageInfo,
		uint32_t descriptorCount = 1)
	{
		return VkWriteDescriptorSet {
		.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
		.pNext = nullptr,
		.dstSet = dstSet,
		.dstBinding = binding,
		.descriptorCount = descriptorCount,
		.descriptorType = type,
		.pImageInfo = imageInfo };
	}

	[[nodiscard]] constexpr VkVertexInputBindingDescription&& vertexInputBindingDescription(
		uint32_t binding,
		uint32_t stride,
		VkVertexInputRate inputRate)
	{
		return VkVertexInputBindingDescription{
		.binding = binding,
		.stride = stride,
		.inputRate = inputRate };
	}

	[[nodiscard]] constexpr VkVertexInputAttributeDescription&& vertexInputAttributeDescription(
		uint32_t binding,
		uint32_t location,
		VkFormat format,
		uint32_t offset)
	{
		return VkVertexInputAttributeDescription{
		.location = location,
		.binding = binding,
		.format = format,
		.offset = offset };
	}

	[[nodiscard]] constexpr VkPipelineVertexInputStateCreateInfo&& pipelineVertexInputStateCreateInfo()
	{
		return VkPipelineVertexInputStateCreateInfo{ .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO, .pNext = nullptr };
	}

	[[nodiscard]] constexpr VkPipelineVertexInputStateCreateInfo&& pipelineVertexInputStateCreateInfo(
		const std::vector<VkVertexInputBindingDescription>& vertexBindingDescriptions,
		const std::vector<VkVertexInputAttributeDescription>& vertexAttributeDescriptions
	)
	{
		return VkPipelineVertexInputStateCreateInfo{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
		.pNext = nullptr,
		.vertexBindingDescriptionCount = static_cast<uint32_t>(vertexBindingDescriptions.size()),
		.pVertexBindingDescriptions = vertexBindingDescriptions.data(),
		.vertexAttributeDescriptionCount = static_cast<uint32_t>(vertexAttributeDescriptions.size()),
		.pVertexAttributeDescriptions = vertexAttributeDescriptions.data() };
	}

	[[nodiscard]] constexpr VkPipelineInputAssemblyStateCreateInfo&& pipelineInputAssemblyStateCreateInfo(
		VkPrimitiveTopology topology,
		VkPipelineInputAssemblyStateCreateFlags flags,
		VkBool32 primitiveRestartEnable)
	{
		return VkPipelineInputAssemblyStateCreateInfo{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = flags,
		.topology = topology,
		.primitiveRestartEnable = primitiveRestartEnable };
	}

	[[nodiscard]] constexpr VkPipelineRasterizationStateCreateInfo&& pipelineRasterizationStateCreateInfo(
		VkPolygonMode polygonMode,
		VkCullModeFlags cullMode,
		VkFrontFace frontFace,
		VkPipelineRasterizationStateCreateFlags flags = 0)
	{
		return VkPipelineRasterizationStateCreateInfo{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = flags,
		.depthClampEnable = VK_FALSE,
		.polygonMode = polygonMode,
		.cullMode = cullMode,
		.frontFace = frontFace,
		.lineWidth = 1.0f };
	}

	[[nodiscard]] constexpr VkPipelineColorBlendAttachmentState&& pipelineColorBlendAttachmentState(
		VkColorComponentFlags colorWriteMask,
		VkBool32 blendEnable)
	{
		return VkPipelineColorBlendAttachmentState{
		.blendEnable = blendEnable,
		.colorWriteMask = colorWriteMask};
	}

	[[nodiscard]] constexpr VkPipelineColorBlendStateCreateInfo&& pipelineColorBlendStateCreateInfo(
		uint32_t attachmentCount,
		const VkPipelineColorBlendAttachmentState* pAttachments)
	{
		return VkPipelineColorBlendStateCreateInfo{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
		.pNext = nullptr,
		.attachmentCount = attachmentCount,
		.pAttachments = pAttachments };
	}

	[[nodiscard]] constexpr VkPipelineDepthStencilStateCreateInfo&& pipelineDepthStencilStateCreateInfo(
		VkBool32 depthTestEnable,
		VkBool32 depthWriteEnable,
		VkCompareOp depthCompareOp)
	{
		return VkPipelineDepthStencilStateCreateInfo{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
		.pNext = nullptr,
		.depthTestEnable = depthTestEnable,
		.depthWriteEnable = depthWriteEnable,
		.depthCompareOp = depthCompareOp,
		.back{.compareOp = VK_COMPARE_OP_ALWAYS} };
	}

	[[nodiscard]] constexpr VkPipelineViewportStateCreateInfo&& pipelineViewportStateCreateInfo(
		uint32_t viewportCount,
		uint32_t scissorCount,
		VkPipelineViewportStateCreateFlags flags = 0)
	{
		return VkPipelineViewportStateCreateInfo{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = flags,
		.viewportCount = viewportCount,
		.scissorCount = scissorCount};
	}

	[[nodiscard]] constexpr VkPipelineMultisampleStateCreateInfo&& pipelineMultisampleStateCreateInfo(
		VkSampleCountFlagBits rasterizationSamples,
		VkPipelineMultisampleStateCreateFlags flags = 0)
	{
		return VkPipelineMultisampleStateCreateInfo{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = flags,
		.rasterizationSamples = rasterizationSamples };
	}

	[[nodiscard]] constexpr VkPipelineDynamicStateCreateInfo pipelineDynamicStateCreateInfo(
		const VkDynamicState* pDynamicStates,
		uint32_t dynamicStateCount,
		VkPipelineDynamicStateCreateFlags flags = 0)
	{
		return VkPipelineDynamicStateCreateInfo{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = flags,
		.dynamicStateCount = dynamicStateCount,
		.pDynamicStates = pDynamicStates };
	}

	[[nodiscard]] constexpr VkPipelineDynamicStateCreateInfo&& pipelineDynamicStateCreateInfo(
		const std::vector<VkDynamicState>& pDynamicStates,
		VkPipelineDynamicStateCreateFlags flags = 0)
	{
		return VkPipelineDynamicStateCreateInfo{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = flags,
		.dynamicStateCount = static_cast<uint32_t>(pDynamicStates.size()),
		.pDynamicStates = pDynamicStates.data() };
	}

	[[nodiscard]] constexpr VkPipelineTessellationStateCreateInfo&& pipelineTessellationStateCreateInfo(uint32_t patchControlPoints)
	{
		return VkPipelineTessellationStateCreateInfo {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO,
		.pNext = nullptr,
		.patchControlPoints = patchControlPoints };
	}

	[[nodiscard]] constexpr VkGraphicsPipelineCreateInfo&& pipelineCreateInfo(
		VkPipelineLayout layout,
		VkRenderPass renderPass,
		VkPipelineCreateFlags flags = 0)
	{
		return VkGraphicsPipelineCreateInfo{
		.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
		.pNext = nullptr,
		.flags = flags,
		.layout = layout,
		.renderPass = renderPass,
		.basePipelineHandle = VK_NULL_HANDLE,
		.basePipelineIndex = -1 };
	}

	[[nodiscard]] constexpr VkGraphicsPipelineCreateInfo&& pipelineCreateInfo()
	{
		return VkGraphicsPipelineCreateInfo{
		.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
		.pNext = nullptr,
		.basePipelineHandle = VK_NULL_HANDLE,
		.basePipelineIndex = -1 };
	}

	[[nodiscard]] constexpr VkComputePipelineCreateInfo&& computePipelineCreateInfo(
		VkPipelineLayout layout,
		VkPipelineCreateFlags flags = 0)
	{
		return VkComputePipelineCreateInfo{
		.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO,
		.pNext = nullptr,
		.flags = flags,
		.layout = layout };
	}

	[[nodiscard]] constexpr VkPushConstantRange&& pushConstantRange(
		VkShaderStageFlags stageFlags,
		uint32_t size,
		uint32_t offset)
	{
		return VkPushConstantRange{
		.stageFlags = stageFlags,
		.offset = offset,
		.size = size };
	}

	[[nodiscard]] constexpr VkBindSparseInfo&& bindSparseInfo()
	{
		return VkBindSparseInfo{ .sType = VK_STRUCTURE_TYPE_BIND_SPARSE_INFO, .pNext = nullptr };
	}

	/** @brief Initialize a map entry for a shader specialization constant */
	[[nodiscard]] constexpr VkSpecializationMapEntry&& specializationMapEntry(uint32_t constantID, uint32_t offset, size_t size)
	{
		return VkSpecializationMapEntry{
		.constantID = constantID,
		.offset = offset,
		.size = size };
	}

	/** @brief Initialize a specialization constant info structure to pass to a shader stage */
	[[nodiscard]] constexpr VkSpecializationInfo&& specializationInfo(uint32_t mapEntryCount, const VkSpecializationMapEntry* mapEntries, size_t dataSize, const void* data)
	{
		return VkSpecializationInfo{
		.mapEntryCount = mapEntryCount,
		.pMapEntries = mapEntries,
		.dataSize = dataSize,
		.pData = data };
	}

	/** @brief Initialize a specialization constant info structure to pass to a shader stage */
	[[nodiscard]] constexpr VkSpecializationInfo&& specializationInfo(const std::vector<VkSpecializationMapEntry>& mapEntries, size_t dataSize, const void* data)
	{
		return VkSpecializationInfo{
		.mapEntryCount = static_cast<uint32_t>(mapEntries.size()),
		.pMapEntries = mapEntries.data(),
		.dataSize = dataSize,
		.pData = data };
	}

	// Ray tracing related
	[[nodiscard]] constexpr VkAccelerationStructureGeometryKHR&& accelerationStructureGeometryKHR()
	{
		return VkAccelerationStructureGeometryKHR{
		.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
		.pNext = nullptr };
	}

	[[nodiscard]] constexpr VkAccelerationStructureBuildGeometryInfoKHR&& accelerationStructureBuildGeometryInfoKHR()
	{
		return VkAccelerationStructureBuildGeometryInfoKHR{
		.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
		.pNext = nullptr };
	}

	[[nodiscard]] constexpr VkAccelerationStructureBuildSizesInfoKHR&& accelerationStructureBuildSizesInfoKHR()
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

	[[nodiscard]] constexpr VkRayTracingPipelineCreateInfoKHR&& rayTracingPipelineCreateInfoKHR()
	{
		return VkRayTracingPipelineCreateInfoKHR{
		.sType = VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_CREATE_INFO_KHR,
		.pNext = nullptr };
	}

	[[nodiscard]] constexpr VkWriteDescriptorSetAccelerationStructureKHR&& writeDescriptorSetAccelerationStructureKHR()
	{
		return VkWriteDescriptorSetAccelerationStructureKHR{
		.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_ACCELERATION_STRUCTURE_KHR,
		.pNext = nullptr };
	}
}