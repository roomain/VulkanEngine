#include "pch.h"
#include "common/enumerate.h"
#include "VulkanDeviceCapabilities.h"
#include "vulkan_enum_to_string.h"
#include "Vulkan_macros.h"
#include "LoggingSystem/Exception.h"
#include "VulkanParameter.h"


VulkanDeviceCapabilities::VulkanDeviceCapabilities(const uint32_t a_deviceIndex, const VkPhysicalDevice a_device) :
	m_deviceIndex{ a_deviceIndex }
{
	enumerate(&vkEnumerateDeviceExtensionProperties, m_extensions, a_device, nullptr);
	enumerate(&vkEnumerateDeviceLayerProperties, m_layersProperties, a_device);
	enumerate(&vkGetPhysicalDeviceQueueFamilyProperties, m_queueFamilies, a_device);
	//------------------------------------------------------------------------------------------------------
	vkGetPhysicalDeviceProperties(a_device, &m_deviceProperties);
	vkGetPhysicalDeviceFeatures(a_device, &m_deviceFeatures);
	vkGetPhysicalDeviceMemoryProperties(a_device, &m_memoryProperties);


	for (int format = VK_FORMAT_R4G4_UNORM_PACK8; format <= VK_FORMAT_ASTC_12x12_SRGB_BLOCK; ++format)
	{
		VkFormatProperties prop;
		vkGetPhysicalDeviceFormatProperties(a_device, static_cast<VkFormat>(format), &prop);
		m_formatsCapabilities.emplace(static_cast<VkFormat>(format), prop);
	}

	for (int format = VK_FORMAT_G8B8G8R8_422_UNORM; format <= VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM; ++format)
	{
		VkFormatProperties prop;
		vkGetPhysicalDeviceFormatProperties(a_device, static_cast<VkFormat>(format), &prop);
		m_formatsCapabilities.emplace(static_cast<VkFormat>(format), prop);
	}

	for (int format = VK_FORMAT_G8_B8R8_2PLANE_444_UNORM; format <= VK_FORMAT_G16_B16R16_2PLANE_444_UNORM; ++format)
	{
		VkFormatProperties prop;
		vkGetPhysicalDeviceFormatProperties(a_device, static_cast<VkFormat>(format), &prop);
		m_formatsCapabilities.emplace(static_cast<VkFormat>(format), prop);
	}

	for (int format = VK_FORMAT_A4R4G4B4_UNORM_PACK16; format <= VK_FORMAT_A4B4G4R4_UNORM_PACK16; ++format)
	{
		VkFormatProperties prop;
		vkGetPhysicalDeviceFormatProperties(a_device, static_cast<VkFormat>(format), &prop);
		m_formatsCapabilities.emplace(static_cast<VkFormat>(format), prop);
	}

	for (int format = VK_FORMAT_ASTC_4x4_SFLOAT_BLOCK; format <= VK_FORMAT_ASTC_12x12_SFLOAT_BLOCK; ++format)
	{
		VkFormatProperties prop;
		vkGetPhysicalDeviceFormatProperties(a_device, static_cast<VkFormat>(format), &prop);
		m_formatsCapabilities.emplace(static_cast<VkFormat>(format), prop);
	}

	for (int format = VK_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG; format <= VK_FORMAT_PVRTC2_4BPP_SRGB_BLOCK_IMG; ++format)
	{
		VkFormatProperties prop;
		vkGetPhysicalDeviceFormatProperties(a_device, static_cast<VkFormat>(format), &prop);
		m_formatsCapabilities.emplace(static_cast<VkFormat>(format), prop);
	}
}

VulkanDeviceInfo VulkanDeviceCapabilities::deviceInfo()const
{
	return VulkanDeviceInfo{
		.deviceIndex = m_deviceIndex,
		.name = std::string{m_deviceProperties.deviceName},
		.deviceType = to_string(m_deviceProperties.deviceType),
		.apiVersion = m_deviceProperties.apiVersion,
		.driverVersion = m_deviceProperties.driverVersion
	};
}


//------------------------------------------------------------------------------------------
VkPresentModeKHR VulkanDeviceCapabilities::bestPresentationMode()const
{
	if (!m_swapChainCapabilities.has_value())
		throw  Exception("Swapchain capabilities not created");
	if (std::find(m_swapChainCapabilities.value().supportedModes.cbegin(), m_swapChainCapabilities.value().supportedModes.cend(), VK_PRESENT_MODE_MAILBOX_KHR) != m_swapChainCapabilities.value().supportedModes.cend())
		return VK_PRESENT_MODE_MAILBOX_KHR;
	return VK_PRESENT_MODE_FIFO_KHR;
}

VkSurfaceFormatKHR VulkanDeviceCapabilities::bestSurfaceFormat()const
{
	if (!m_swapChainCapabilities.has_value())
		throw  Exception("Swapchain capabilities not created");

	// If only 1 format available and is undefined, then this means ALL formats are available (no restrictions)
	if (m_swapChainCapabilities.value().supportedFormats.size() == 1 && m_swapChainCapabilities.value().supportedFormats[0].format == VK_FORMAT_UNDEFINED)
		return{ VK_FORMAT_R8G8B8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };

	// If restricted, search for optimal format
	auto iter = std::find_if(m_swapChainCapabilities.value().supportedFormats.begin(), m_swapChainCapabilities.value().supportedFormats.end(), [&](const auto& format)
		{
			return (format.format == VK_FORMAT_R8G8B8A8_UNORM || format.format == VK_FORMAT_B8G8R8A8_UNORM)
				&& format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
		});
	if (iter != m_swapChainCapabilities.value().supportedFormats.end())
		return *iter;

	// If can't find optimal format, then just return first format
	return m_swapChainCapabilities.value().supportedFormats[0];
}

bool VulkanDeviceCapabilities::isFeaturesAvailable(const VulkanDeviceFeatures& a_features)const
{
	bool bAvailable = static_cast<bool>(m_deviceFeatures.robustBufferAccess) || (static_cast<bool>(m_deviceFeatures.robustBufferAccess) == a_features.robustBufferAccess);
	bAvailable |= static_cast<bool>(m_deviceFeatures.fullDrawIndexUint32) || (static_cast<bool>(m_deviceFeatures.fullDrawIndexUint32) == a_features.fullDrawIndexUint32);
	bAvailable |= static_cast<bool>(m_deviceFeatures.imageCubeArray) || (static_cast<bool>(m_deviceFeatures.imageCubeArray) == a_features.imageCubeArray);
	bAvailable |= static_cast<bool>(m_deviceFeatures.independentBlend) || (static_cast<bool>(m_deviceFeatures.independentBlend) == a_features.independentBlend);
	bAvailable |= static_cast<bool>(m_deviceFeatures.geometryShader) || (static_cast<bool>(m_deviceFeatures.geometryShader) == a_features.geometryShader);
	bAvailable |= static_cast<bool>(m_deviceFeatures.tessellationShader) || (static_cast<bool>(m_deviceFeatures.tessellationShader) == a_features.tessellationShader);
	bAvailable |= static_cast<bool>(m_deviceFeatures.sampleRateShading) || (static_cast<bool>(m_deviceFeatures.sampleRateShading) == a_features.sampleRateShading);
	bAvailable |= static_cast<bool>(m_deviceFeatures.dualSrcBlend) || (static_cast<bool>(m_deviceFeatures.dualSrcBlend) == a_features.dualSrcBlend);
	bAvailable |= static_cast<bool>(m_deviceFeatures.logicOp) || (static_cast<bool>(m_deviceFeatures.logicOp) == a_features.logicOp);
	bAvailable |= static_cast<bool>(m_deviceFeatures.multiDrawIndirect) || (static_cast<bool>(m_deviceFeatures.multiDrawIndirect) == a_features.multiDrawIndirect);
	bAvailable |= static_cast<bool>(m_deviceFeatures.drawIndirectFirstInstance) || (static_cast<bool>(m_deviceFeatures.drawIndirectFirstInstance) == a_features.drawIndirectFirstInstance);
	bAvailable |= static_cast<bool>(m_deviceFeatures.depthClamp) || (static_cast<bool>(m_deviceFeatures.depthClamp) == a_features.depthClamp);
	bAvailable |= static_cast<bool>(m_deviceFeatures.depthBiasClamp) || (static_cast<bool>(m_deviceFeatures.depthBiasClamp) == a_features.depthBiasClamp);
	bAvailable |= static_cast<bool>(m_deviceFeatures.fillModeNonSolid) || (static_cast<bool>(m_deviceFeatures.fillModeNonSolid) == a_features.fillModeNonSolid);
	bAvailable |= static_cast<bool>(m_deviceFeatures.depthBounds) || (static_cast<bool>(m_deviceFeatures.depthBounds) == a_features.depthBounds);
	bAvailable |= static_cast<bool>(m_deviceFeatures.wideLines) || (static_cast<bool>(m_deviceFeatures.wideLines) == a_features.wideLines);
	bAvailable |= static_cast<bool>(m_deviceFeatures.largePoints) || (static_cast<bool>(m_deviceFeatures.largePoints) == a_features.largePoints);
	bAvailable |= static_cast<bool>(m_deviceFeatures.alphaToOne) || (static_cast<bool>(m_deviceFeatures.alphaToOne) == a_features.alphaToOne);
	bAvailable |= static_cast<bool>(m_deviceFeatures.multiViewport) || (static_cast<bool>(m_deviceFeatures.multiViewport) == a_features.multiViewport);
	bAvailable |= static_cast<bool>(m_deviceFeatures.samplerAnisotropy) || (static_cast<bool>(m_deviceFeatures.samplerAnisotropy) == a_features.samplerAnisotropy);
	bAvailable |= static_cast<bool>(m_deviceFeatures.textureCompressionETC2) || (static_cast<bool>(m_deviceFeatures.textureCompressionETC2) == a_features.textureCompressionETC2);
	bAvailable |= static_cast<bool>(m_deviceFeatures.textureCompressionASTC_LDR) || (static_cast<bool>(m_deviceFeatures.textureCompressionASTC_LDR) == a_features.textureCompressionASTC_LDR);
	bAvailable |= static_cast<bool>(m_deviceFeatures.textureCompressionBC) || (static_cast<bool>(m_deviceFeatures.textureCompressionBC) == a_features.textureCompressionBC);
	bAvailable |= static_cast<bool>(m_deviceFeatures.occlusionQueryPrecise) || (static_cast<bool>(m_deviceFeatures.occlusionQueryPrecise) == a_features.occlusionQueryPrecise);
	bAvailable |= static_cast<bool>(m_deviceFeatures.pipelineStatisticsQuery) || (static_cast<bool>(m_deviceFeatures.pipelineStatisticsQuery) == a_features.pipelineStatisticsQuery);
	bAvailable |= static_cast<bool>(m_deviceFeatures.vertexPipelineStoresAndAtomics) || (static_cast<bool>(m_deviceFeatures.vertexPipelineStoresAndAtomics) == a_features.vertexPipelineStoresAndAtomics);
	bAvailable |= static_cast<bool>(m_deviceFeatures.fragmentStoresAndAtomics) || (static_cast<bool>(m_deviceFeatures.fragmentStoresAndAtomics) == a_features.fragmentStoresAndAtomics);
	bAvailable |= static_cast<bool>(m_deviceFeatures.shaderTessellationAndGeometryPointSize) || (static_cast<bool>(m_deviceFeatures.shaderTessellationAndGeometryPointSize) == a_features.shaderTessellationAndGeometryPointSize);
	bAvailable |= static_cast<bool>(m_deviceFeatures.shaderImageGatherExtended) || (static_cast<bool>(m_deviceFeatures.shaderImageGatherExtended) == a_features.shaderImageGatherExtended);
	bAvailable |= static_cast<bool>(m_deviceFeatures.shaderStorageImageExtendedFormats) || (static_cast<bool>(m_deviceFeatures.shaderStorageImageExtendedFormats) == a_features.shaderStorageImageExtendedFormats);
	bAvailable |= static_cast<bool>(m_deviceFeatures.shaderStorageImageMultisample) || (static_cast<bool>(m_deviceFeatures.shaderStorageImageMultisample) == a_features.shaderStorageImageMultisample);
	bAvailable |= static_cast<bool>(m_deviceFeatures.shaderStorageImageReadWithoutFormat) || (static_cast<bool>(m_deviceFeatures.shaderStorageImageReadWithoutFormat) == a_features.shaderStorageImageReadWithoutFormat);
	bAvailable |= static_cast<bool>(m_deviceFeatures.shaderStorageImageWriteWithoutFormat) || (static_cast<bool>(m_deviceFeatures.shaderStorageImageWriteWithoutFormat) == a_features.shaderStorageImageWriteWithoutFormat);
	bAvailable |= static_cast<bool>(m_deviceFeatures.shaderUniformBufferArrayDynamicIndexing) || (static_cast<bool>(m_deviceFeatures.shaderUniformBufferArrayDynamicIndexing) == a_features.shaderUniformBufferArrayDynamicIndexing);
	bAvailable |= static_cast<bool>(m_deviceFeatures.shaderSampledImageArrayDynamicIndexing) || (static_cast<bool>(m_deviceFeatures.shaderSampledImageArrayDynamicIndexing) == a_features.shaderSampledImageArrayDynamicIndexing);
	bAvailable |= static_cast<bool>(m_deviceFeatures.shaderStorageBufferArrayDynamicIndexing) || (static_cast<bool>(m_deviceFeatures.shaderStorageBufferArrayDynamicIndexing) == a_features.shaderStorageBufferArrayDynamicIndexing);
	bAvailable |= static_cast<bool>(m_deviceFeatures.shaderStorageImageArrayDynamicIndexing) || (static_cast<bool>(m_deviceFeatures.shaderStorageImageArrayDynamicIndexing) == a_features.shaderStorageImageArrayDynamicIndexing);
	bAvailable |= static_cast<bool>(m_deviceFeatures.shaderClipDistance) || (static_cast<bool>(m_deviceFeatures.shaderClipDistance) == a_features.shaderClipDistance);
	bAvailable |= static_cast<bool>(m_deviceFeatures.shaderCullDistance) || (static_cast<bool>(m_deviceFeatures.shaderCullDistance) == a_features.shaderCullDistance);
	bAvailable |= static_cast<bool>(m_deviceFeatures.shaderFloat64) || (static_cast<bool>(m_deviceFeatures.shaderFloat64) == a_features.shaderFloat64);
	bAvailable |= static_cast<bool>(m_deviceFeatures.shaderInt64) || (static_cast<bool>(m_deviceFeatures.shaderInt64) == a_features.shaderInt64);
	bAvailable |= static_cast<bool>(m_deviceFeatures.shaderInt16) || (static_cast<bool>(m_deviceFeatures.shaderInt16) == a_features.shaderInt16);
	bAvailable |= static_cast<bool>(m_deviceFeatures.shaderResourceResidency) || (static_cast<bool>(m_deviceFeatures.shaderResourceResidency) == a_features.shaderResourceResidency);
	bAvailable |= static_cast<bool>(m_deviceFeatures.shaderResourceMinLod) || (static_cast<bool>(m_deviceFeatures.shaderResourceMinLod) == a_features.shaderResourceMinLod);
	bAvailable |= static_cast<bool>(m_deviceFeatures.sparseBinding) || (static_cast<bool>(m_deviceFeatures.sparseBinding) == a_features.sparseBinding);
	bAvailable |= static_cast<bool>(m_deviceFeatures.sparseResidencyBuffer) || (static_cast<bool>(m_deviceFeatures.sparseResidencyBuffer) == a_features.sparseResidencyBuffer);
	bAvailable |= static_cast<bool>(m_deviceFeatures.sparseResidencyImage2D) || (static_cast<bool>(m_deviceFeatures.sparseResidencyImage2D) == a_features.sparseResidencyImage2D);
	bAvailable |= static_cast<bool>(m_deviceFeatures.sparseResidencyImage3D) || (static_cast<bool>(m_deviceFeatures.sparseResidencyImage3D) == a_features.sparseResidencyImage3D);
	bAvailable |= static_cast<bool>(m_deviceFeatures.sparseResidency2Samples) || (static_cast<bool>(m_deviceFeatures.sparseResidency2Samples) == a_features.sparseResidency2Samples);
	bAvailable |= static_cast<bool>(m_deviceFeatures.sparseResidency4Samples) || (static_cast<bool>(m_deviceFeatures.sparseResidency4Samples) == a_features.sparseResidency4Samples);
	bAvailable |= static_cast<bool>(m_deviceFeatures.sparseResidency8Samples) || (static_cast<bool>(m_deviceFeatures.sparseResidency8Samples) == a_features.sparseResidency8Samples);
	bAvailable |= static_cast<bool>(m_deviceFeatures.sparseResidency16Samples) || (static_cast<bool>(m_deviceFeatures.sparseResidency16Samples) == a_features.sparseResidency16Samples);
	bAvailable |= static_cast<bool>(m_deviceFeatures.sparseResidencyAliased) || (static_cast<bool>(m_deviceFeatures.sparseResidencyAliased) == a_features.sparseResidencyAliased);
	bAvailable |= static_cast<bool>(m_deviceFeatures.variableMultisampleRate) || (static_cast<bool>(m_deviceFeatures.variableMultisampleRate) == a_features.variableMultisampleRate);
	bAvailable |= static_cast<bool>(m_deviceFeatures.inheritedQueries) || (static_cast<bool>(m_deviceFeatures.inheritedQueries) == a_features.inheritedQueries);
	return bAvailable;
}

VkPhysicalDeviceFeatures VulkanDeviceCapabilities::toFeatures(const VulkanDeviceFeatures& a_features)
{
	return VkPhysicalDeviceFeatures
	{
		a_features.robustBufferAccess,
		a_features.fullDrawIndexUint32,
		a_features.imageCubeArray,
		a_features.independentBlend,
		a_features.geometryShader,
		a_features.tessellationShader,
		a_features.sampleRateShading,
		a_features.dualSrcBlend,
		a_features.logicOp,
		a_features.multiDrawIndirect,
		a_features.drawIndirectFirstInstance,
		a_features.depthClamp,
		a_features.depthBiasClamp,
		a_features.fillModeNonSolid,
		a_features.depthBounds,
		a_features.wideLines,
		a_features.largePoints,
		a_features.alphaToOne,
		a_features.multiViewport,
		a_features.samplerAnisotropy,
		a_features.textureCompressionETC2,
		a_features.textureCompressionASTC_LDR,
		a_features.textureCompressionBC,
		a_features.occlusionQueryPrecise,
		a_features.pipelineStatisticsQuery,
		a_features.vertexPipelineStoresAndAtomics,
		a_features.fragmentStoresAndAtomics,
		a_features.shaderTessellationAndGeometryPointSize,
		a_features.shaderImageGatherExtended,
		a_features.shaderStorageImageExtendedFormats,
		a_features.shaderStorageImageMultisample,
		a_features.shaderStorageImageReadWithoutFormat,
		a_features.shaderStorageImageWriteWithoutFormat,
		a_features.shaderUniformBufferArrayDynamicIndexing,
		a_features.shaderSampledImageArrayDynamicIndexing,
		a_features.shaderStorageBufferArrayDynamicIndexing,
		a_features.shaderStorageImageArrayDynamicIndexing,
		a_features.shaderClipDistance,
		a_features.shaderCullDistance,
		a_features.shaderFloat64,
		a_features.shaderInt64,
		a_features.shaderInt16,
		a_features.shaderResourceResidency,
		a_features.shaderResourceMinLod,
		a_features.sparseBinding,
		a_features.sparseResidencyBuffer,
		a_features.sparseResidencyImage2D,
		a_features.sparseResidencyImage3D,
		a_features.sparseResidency2Samples,
		a_features.sparseResidency4Samples,
		a_features.sparseResidency8Samples,
		a_features.sparseResidency16Samples,
		a_features.sparseResidencyAliased,
		a_features.variableMultisampleRate,
		a_features.inheritedQueries
	};
}

void VulkanDeviceCapabilities::findQueues(const bool a_presentation, const VkQueueFlags a_flags, std::vector<int>& a_queuesIndex, VkPhysicalDevice a_physicalDevice, VkSurfaceKHR a_surface)const
{
	uint32_t queueFamilyIndex = 0;
	for (const auto& prop : m_queueFamilies)
	{
		if ((prop.queueFlags & a_flags) == a_flags)
		{
			if (a_presentation)
			{
				VkBool32 supported = false;
				VK_CHECK_LOG(vkGetPhysicalDeviceSurfaceSupportKHR(a_physicalDevice, queueFamilyIndex, a_surface, &supported))
				if (supported)
					a_queuesIndex.emplace_back(queueFamilyIndex);
			}
		}
		++queueFamilyIndex;
	}
}