#include "pch.h"
#include "vk_display.h"
#include "IDisplayer.h"
#include "vk_enum_to_string.h"
#include "vk_ext_struct.h"
#include <vector>


namespace Vulkan
{
	//-------------------------------------------
	// auxiliary functions
	//-------------------------------------------
	void displayDeviceLimits(const VkPhysicalDeviceLimits& a_limits, IDisplayer& a_displayer)
	{
		a_displayer.beginNode("Physical Device limits");
		a_displayer.attribute("maxImageDimension1D", a_limits.maxImageDimension1D);
		a_displayer.attribute("maxImageDimension2D", a_limits.maxImageDimension2D);
		a_displayer.attribute("maxImageDimension3D", a_limits.maxImageDimension3D);
		a_displayer.attribute("maxImageDimensionCube", a_limits.maxImageDimensionCube);
		a_displayer.attribute("maxImageArrayLayers", a_limits.maxImageArrayLayers);
		a_displayer.attribute("maxTexelBufferElements", a_limits.maxTexelBufferElements);
		a_displayer.attribute("maxUniformBufferRange", a_limits.maxUniformBufferRange);
		a_displayer.attribute("maxStorageBufferRange", a_limits.maxStorageBufferRange);
		a_displayer.attribute("maxPushConstantsSize", a_limits.maxPushConstantsSize);
		a_displayer.attribute("maxMemoryAllocationCount", a_limits.maxMemoryAllocationCount);
		a_displayer.attribute("maxSamplerAllocationCount", a_limits.maxSamplerAllocationCount);
		a_displayer.attribute("bufferImageGranularity", static_cast<size_t>(a_limits.bufferImageGranularity));
		a_displayer.attribute("sparseAddressSpaceSize", static_cast<size_t>(a_limits.sparseAddressSpaceSize));
		a_displayer.attribute("maxBoundDescriptorSets", a_limits.maxBoundDescriptorSets);
		a_displayer.attribute("maxPerStageDescriptorSamplers", a_limits.maxPerStageDescriptorSamplers);
		a_displayer.attribute("maxPerStageDescriptorUniformBuffers", a_limits.maxPerStageDescriptorUniformBuffers);
		a_displayer.attribute("maxPerStageDescriptorStorageBuffers", a_limits.maxPerStageDescriptorStorageBuffers);
		a_displayer.attribute("maxPerStageDescriptorSampledImages", a_limits.maxPerStageDescriptorSampledImages);
		a_displayer.attribute("maxPerStageDescriptorStorageImages", a_limits.maxPerStageDescriptorStorageImages);
		a_displayer.attribute("maxPerStageDescriptorInputAttachments", a_limits.maxPerStageDescriptorInputAttachments);
		a_displayer.attribute("maxPerStageResources", a_limits.maxPerStageResources);
		a_displayer.attribute("maxDescriptorSetSamplers", a_limits.maxDescriptorSetSamplers);
		a_displayer.attribute("maxDescriptorSetUniformBuffers", a_limits.maxDescriptorSetUniformBuffers);
		a_displayer.attribute("maxDescriptorSetUniformBuffersDynamic", a_limits.maxDescriptorSetUniformBuffersDynamic);
		a_displayer.attribute("maxDescriptorSetStorageBuffers", a_limits.maxDescriptorSetStorageBuffers);
		a_displayer.attribute("maxDescriptorSetStorageBuffersDynamic", a_limits.maxDescriptorSetStorageBuffersDynamic);
		a_displayer.attribute("maxDescriptorSetSampledImages", a_limits.maxDescriptorSetSampledImages);
		a_displayer.attribute("maxDescriptorSetStorageImages", a_limits.maxDescriptorSetStorageImages);
		a_displayer.attribute("maxDescriptorSetInputAttachments", a_limits.maxDescriptorSetInputAttachments);
		a_displayer.attribute("maxVertexInputAttributes", a_limits.maxVertexInputAttributes);
		a_displayer.attribute("maxVertexInputBindings", a_limits.maxVertexInputBindings);
		a_displayer.attribute("maxVertexInputAttributeOffset", a_limits.maxVertexInputAttributeOffset);
		a_displayer.attribute("maxVertexInputBindingStride", a_limits.maxVertexInputBindingStride);
		a_displayer.attribute("maxVertexOutputComponents", a_limits.maxVertexOutputComponents);
		a_displayer.attribute("maxTessellationGenerationLevel", a_limits.maxTessellationGenerationLevel);
		a_displayer.attribute("maxTessellationPatchSize", a_limits.maxTessellationPatchSize);
		a_displayer.attribute("maxTessellationControlPerVertexInputComponents", a_limits.maxTessellationControlPerVertexInputComponents);
		a_displayer.attribute("maxTessellationControlPerVertexOutputComponents", a_limits.maxTessellationControlPerVertexOutputComponents);
		a_displayer.attribute("maxTessellationControlPerPatchOutputComponents", a_limits.maxTessellationControlPerPatchOutputComponents);
		a_displayer.attribute("maxTessellationControlTotalOutputComponents", a_limits.maxTessellationControlTotalOutputComponents);
		a_displayer.attribute("maxTessellationEvaluationInputComponents", a_limits.maxTessellationEvaluationInputComponents);
		a_displayer.attribute("maxTessellationEvaluationOutputComponents", a_limits.maxTessellationEvaluationOutputComponents);
		a_displayer.attribute("maxGeometryShaderInvocations", a_limits.maxGeometryShaderInvocations);
		a_displayer.attribute("maxGeometryInputComponents", a_limits.maxGeometryInputComponents);
		a_displayer.attribute("maxGeometryOutputComponents", a_limits.maxGeometryOutputComponents);
		a_displayer.attribute("maxGeometryOutputVertices", a_limits.maxGeometryOutputVertices);
		a_displayer.attribute("maxGeometryTotalOutputComponents", a_limits.maxGeometryTotalOutputComponents);
		a_displayer.attribute("maxFragmentInputComponents", a_limits.maxFragmentInputComponents);
		a_displayer.attribute("maxFragmentOutputAttachments", a_limits.maxFragmentOutputAttachments);
		a_displayer.attribute("maxFragmentDualSrcAttachments", a_limits.maxFragmentDualSrcAttachments);
		a_displayer.attribute("maxFragmentCombinedOutputResources", a_limits.maxFragmentCombinedOutputResources);
		a_displayer.attribute("maxComputeSharedMemorySize", a_limits.maxComputeSharedMemorySize);
		a_displayer.attribute("maxComputeWorkGroupCount[0]", a_limits.maxComputeWorkGroupCount[0]);
		a_displayer.attribute("maxComputeWorkGroupCount[1]", a_limits.maxComputeWorkGroupCount[1]);
		a_displayer.attribute("maxComputeWorkGroupCount[2]", a_limits.maxComputeWorkGroupCount[2]);
		a_displayer.attribute("maxComputeWorkGroupInvocations", a_limits.maxComputeWorkGroupInvocations);
		a_displayer.attribute("maxComputeWorkGroupSize[0]", a_limits.maxComputeWorkGroupSize[0]);
		a_displayer.attribute("maxComputeWorkGroupSize[1]", a_limits.maxComputeWorkGroupSize[1]);
		a_displayer.attribute("maxComputeWorkGroupSize[2]", a_limits.maxComputeWorkGroupSize[2]);
		a_displayer.attribute("subPixelPrecisionBits", a_limits.subPixelPrecisionBits);
		a_displayer.attribute("subTexelPrecisionBits", a_limits.subTexelPrecisionBits);
		a_displayer.attribute("mipmapPrecisionBits", a_limits.mipmapPrecisionBits);
		a_displayer.attribute("maxDrawIndexedIndexValue", a_limits.maxDrawIndexedIndexValue);
		a_displayer.attribute("maxDrawIndirectCount", a_limits.maxDrawIndirectCount);
		a_displayer.attribute("maxSamplerLodBias", a_limits.maxSamplerLodBias);
		a_displayer.attribute("maxSamplerAnisotropy", a_limits.maxSamplerAnisotropy);
		a_displayer.attribute("maxViewports", a_limits.maxViewports);
		a_displayer.attribute("maxViewportDimensions[0]", a_limits.maxViewportDimensions[0]);
		a_displayer.attribute("maxViewportDimensions[1]", a_limits.maxViewportDimensions[1]);
		a_displayer.attribute("viewportBoundsRange[0]", a_limits.viewportBoundsRange[0]);
		a_displayer.attribute("viewportBoundsRange[1]", a_limits.viewportBoundsRange[1]);
		a_displayer.attribute("viewportSubPixelBits", a_limits.viewportSubPixelBits);
		a_displayer.attribute("minMemoryMapAlignment", a_limits.minMemoryMapAlignment);
		a_displayer.attribute("minTexelBufferOffsetAlignment", static_cast<size_t>(a_limits.minTexelBufferOffsetAlignment));
		a_displayer.attribute("minUniformBufferOffsetAlignment", static_cast<size_t>(a_limits.minUniformBufferOffsetAlignment));
		a_displayer.attribute("minStorageBufferOffsetAlignment", static_cast<size_t>(a_limits.minStorageBufferOffsetAlignment));
		a_displayer.attribute("minTexelOffset", a_limits.minTexelOffset);
		a_displayer.attribute("maxTexelOffset", a_limits.maxTexelOffset);
		a_displayer.attribute("minTexelGatherOffset", a_limits.minTexelGatherOffset);
		a_displayer.attribute("maxTexelGatherOffset", a_limits.maxTexelGatherOffset);
		a_displayer.attribute("minInterpolationOffset", a_limits.minInterpolationOffset);
		a_displayer.attribute("maxInterpolationOffset", a_limits.maxInterpolationOffset);
		a_displayer.attribute("subPixelInterpolationOffsetBits", a_limits.subPixelInterpolationOffsetBits);
		a_displayer.attribute("maxFramebufferWidth", a_limits.maxFramebufferWidth);
		a_displayer.attribute("maxFramebufferHeight", a_limits.maxFramebufferHeight);
		a_displayer.attribute("maxFramebufferLayers", a_limits.maxFramebufferLayers);
		a_displayer.attribute("framebufferColorSampleCounts", Flag<VkSampleCountFlagBits>::to_string(a_limits.framebufferColorSampleCounts));
		a_displayer.attribute("framebufferDepthSampleCounts", Flag<VkSampleCountFlagBits>::to_string(a_limits.framebufferDepthSampleCounts));
		a_displayer.attribute("framebufferStencilSampleCounts", Flag<VkSampleCountFlagBits>::to_string(a_limits.framebufferStencilSampleCounts));
		a_displayer.attribute("framebufferNoAttachmentsSampleCounts", Flag<VkSampleCountFlagBits>::to_string(a_limits.framebufferNoAttachmentsSampleCounts));
		a_displayer.attribute("maxColorAttachments", a_limits.maxColorAttachments);
		a_displayer.attribute("sampledImageColorSampleCounts", Flag<VkSampleCountFlagBits>::to_string(a_limits.sampledImageColorSampleCounts));
		a_displayer.attribute("sampledImageIntegerSampleCounts", Flag<VkSampleCountFlagBits>::to_string(a_limits.sampledImageIntegerSampleCounts));
		a_displayer.attribute("sampledImageDepthSampleCounts", Flag<VkSampleCountFlagBits>::to_string(a_limits.sampledImageDepthSampleCounts));
		a_displayer.attribute("sampledImageStencilSampleCounts", Flag<VkSampleCountFlagBits>::to_string(a_limits.sampledImageStencilSampleCounts));
		a_displayer.attribute("storageImageSampleCounts", Flag<VkSampleCountFlagBits>::to_string(a_limits.storageImageSampleCounts));
		a_displayer.attribute("maxSampleMaskWords", a_limits.maxSampleMaskWords);
		a_displayer.attribute("timestampComputeAndGraphics", a_limits.timestampComputeAndGraphics);
		a_displayer.attribute("timestampPeriod", a_limits.timestampPeriod);
		a_displayer.attribute("maxClipDistances", a_limits.maxClipDistances);
		a_displayer.attribute("maxCullDistances", a_limits.maxCullDistances);
		a_displayer.attribute("maxCombinedClipAndCullDistances", a_limits.maxCombinedClipAndCullDistances);
		a_displayer.attribute("discreteQueuePriorities", a_limits.discreteQueuePriorities);
		a_displayer.attribute("pointSizeRange[0]", a_limits.pointSizeRange[0]);
		a_displayer.attribute("pointSizeRange[1]", a_limits.pointSizeRange[1]);
		a_displayer.attribute("lineWidthRange[0]", a_limits.lineWidthRange[0]);
		a_displayer.attribute("lineWidthRange[1]", a_limits.lineWidthRange[1]);
		a_displayer.attribute("pointSizeGranularity", a_limits.pointSizeGranularity);
		a_displayer.attribute("lineWidthGranularity", a_limits.lineWidthGranularity);
		a_displayer.attribute("strictLines", a_limits.strictLines);
		a_displayer.attribute("standardSampleLocations", a_limits.standardSampleLocations);
		a_displayer.attribute("optimalBufferCopyOffsetAlignment", static_cast<size_t>(a_limits.optimalBufferCopyOffsetAlignment));
		a_displayer.attribute("optimalBufferCopyRowPitchAlignment", static_cast<size_t>(a_limits.optimalBufferCopyRowPitchAlignment));
		a_displayer.attribute("nonCoherentAtomSize", static_cast<size_t>(a_limits.nonCoherentAtomSize));
		a_displayer.endNode();
	}

	void displayDeviceSparseProps(const VkPhysicalDeviceSparseProperties& a_props, IDisplayer& a_displayer)
	{
		a_displayer.beginNode("Device Sparse properties");
		a_displayer.attribute("residencyStandard2DBlockShape", a_props.residencyStandard2DBlockShape);
		a_displayer.attribute("residencyStandard2DMultisampleBlockShape", a_props.residencyStandard2DMultisampleBlockShape);
		a_displayer.attribute("residencyStandard3DBlockShape", a_props.residencyStandard3DBlockShape);
		a_displayer.attribute("residencyAlignedMipSize", a_props.residencyAlignedMipSize);
		a_displayer.attribute("residencyNonResidentStrict", a_props.residencyNonResidentStrict);
		a_displayer.endNode();
	}
	//-----------------------------------------------------------------------------------------------------------------
	void displayDeviceproperties(const VkPhysicalDeviceProperties& a_deviceProperties, IDisplayer& a_displayer)
	{
		a_displayer.attribute("deviceName", a_deviceProperties.deviceName);
		a_displayer.attribute("deviceType", to_string(a_deviceProperties.deviceType));
		a_displayer.attribute("apiVersion", static_cast<unsigned int>(a_deviceProperties.apiVersion));
		a_displayer.attribute("driverVersion", static_cast<unsigned int>(a_deviceProperties.driverVersion));
		a_displayer.attribute("vendorID", static_cast<unsigned int>(a_deviceProperties.vendorID));
		a_displayer.attribute("deviceID", static_cast<unsigned int>(a_deviceProperties.deviceID));

		displayDeviceLimits(a_deviceProperties.limits, a_displayer);
		displayDeviceSparseProps(a_deviceProperties.sparseProperties, a_displayer);
	}

	void displayDeviceQueuesproperties(const std::vector<VkQueueFamilyProperties>& a_queueFamilies, IDisplayer& a_displayer)
	{
		a_displayer.beginNode("Device Queues");
		for (const auto& familyProp : a_queueFamilies)
		{
			a_displayer.beginNode("Queue");
			a_displayer.attribute("count", familyProp.queueCount);
			a_displayer.attribute("flag", Flag<VkQueueFlagBits>::to_string(familyProp.queueFlags));
			a_displayer.attribute("image granularity width", familyProp.minImageTransferGranularity.width);
			a_displayer.attribute("image granularity height", familyProp.minImageTransferGranularity.height);
			a_displayer.attribute("image granularity depth", familyProp.minImageTransferGranularity.depth);
			a_displayer.endNode();
		}
		a_displayer.endNode();
	}

	void displayDeviceMemoryProperties(const VkPhysicalDeviceMemoryProperties& a_memPops, IDisplayer& a_displayer)
	{
		a_displayer.beginNode("Device Memory");

		a_displayer.beginNode("Memory Types");
		for (uint32_t i = 0; i < a_memPops.memoryTypeCount; ++i)
		{
			a_displayer.beginNode("Type");
			a_displayer.attribute("property flags", Flag<VkMemoryPropertyFlagBits>::to_string(a_memPops.memoryTypes[i].propertyFlags));
			a_displayer.attribute("index", a_memPops.memoryTypes[i].heapIndex);
			a_displayer.endNode();
		}
		a_displayer.endNode();

		a_displayer.beginNode("Memory heaps");
		for (uint32_t i = 0; i < a_memPops.memoryHeapCount; ++i)
		{
			a_displayer.beginNode("Heap");
			a_displayer.attribute("flags", Flag<VkMemoryHeapFlagBits>::to_string(a_memPops.memoryHeaps[i].flags));
			a_displayer.attribute("size", a_memPops.memoryHeaps[i].size);
			a_displayer.endNode();
		}
		a_displayer.endNode();

		a_displayer.endNode();
	}

	void displayDeviceFeatures(const VkPhysicalDeviceFeatures& a_features, IDisplayer& a_displayer)
	{
		a_displayer.beginNode("Device Features");

		a_displayer.attribute("robustBufferAccess",static_cast<bool>(a_features.robustBufferAccess));
		a_displayer.attribute("fullDrawIndexUint32",static_cast<bool>(a_features.fullDrawIndexUint32));
		a_displayer.attribute("imageCubeArray",static_cast<bool>(a_features.imageCubeArray));
		a_displayer.attribute("independentBlend",static_cast<bool>(a_features.independentBlend));
		a_displayer.attribute("geometryShader",static_cast<bool>(a_features.geometryShader));
		a_displayer.attribute("tessellationShader",static_cast<bool>(a_features.tessellationShader));
		a_displayer.attribute("sampleRateShading",static_cast<bool>(a_features.sampleRateShading));
		a_displayer.attribute("dualSrcBlend",static_cast<bool>(a_features.dualSrcBlend));
		a_displayer.attribute("logicOp",static_cast<bool>(a_features.logicOp));
		a_displayer.attribute("multiDrawIndirect",static_cast<bool>(a_features.multiDrawIndirect));
		a_displayer.attribute("drawIndirectFirstInstance",static_cast<bool>(a_features.drawIndirectFirstInstance));
		a_displayer.attribute("depthClamp",static_cast<bool>(a_features.depthClamp));
		a_displayer.attribute("depthBiasClamp",static_cast<bool>(a_features.depthBiasClamp));
		a_displayer.attribute("fillModeNonSolid",static_cast<bool>(a_features.fillModeNonSolid));
		a_displayer.attribute("depthBounds",static_cast<bool>(a_features.depthBounds));
		a_displayer.attribute("wideLines",static_cast<bool>(a_features.wideLines));
		a_displayer.attribute("largePoints",static_cast<bool>(a_features.largePoints));
		a_displayer.attribute("alphaToOne",static_cast<bool>(a_features.alphaToOne));
		a_displayer.attribute("multiViewport",static_cast<bool>(a_features.multiViewport));
		a_displayer.attribute("samplerAnisotropy",static_cast<bool>(a_features.samplerAnisotropy));
		a_displayer.attribute("textureCompressionETC2",static_cast<bool>(a_features.textureCompressionETC2));
		a_displayer.attribute("textureCompressionASTC_LDR",static_cast<bool>(a_features.textureCompressionASTC_LDR));
		a_displayer.attribute("textureCompressionBC",static_cast<bool>(a_features.textureCompressionBC));
		a_displayer.attribute("occlusionQueryPrecise",static_cast<bool>(a_features.occlusionQueryPrecise));
		a_displayer.attribute("pipelineStatisticsQuery",static_cast<bool>(a_features.pipelineStatisticsQuery));
		a_displayer.attribute("vertexPipelineStoresAndAtomics",static_cast<bool>(a_features.vertexPipelineStoresAndAtomics));
		a_displayer.attribute("fragmentStoresAndAtomics",static_cast<bool>(a_features.fragmentStoresAndAtomics));
		a_displayer.attribute("shaderTessellationAndGeometryPointSize",static_cast<bool>(a_features.shaderTessellationAndGeometryPointSize));
		a_displayer.attribute("shaderImageGatherExtended",static_cast<bool>(a_features.shaderImageGatherExtended));
		a_displayer.attribute("shaderStorageImageExtendedFormats",static_cast<bool>(a_features.shaderStorageImageExtendedFormats));
		a_displayer.attribute("shaderStorageImageMultisample",static_cast<bool>(a_features.shaderStorageImageMultisample));
		a_displayer.attribute("shaderStorageImageReadWithoutFormat",static_cast<bool>(a_features.shaderStorageImageReadWithoutFormat));
		a_displayer.attribute("shaderStorageImageWriteWithoutFormat",static_cast<bool>(a_features.shaderStorageImageWriteWithoutFormat));
		a_displayer.attribute("shaderUniformBufferArrayDynamicIndexing",static_cast<bool>(a_features.shaderUniformBufferArrayDynamicIndexing));
		a_displayer.attribute("shaderSampledImageArrayDynamicIndexing",static_cast<bool>(a_features.shaderSampledImageArrayDynamicIndexing));
		a_displayer.attribute("shaderStorageBufferArrayDynamicIndexing",static_cast<bool>(a_features.shaderStorageBufferArrayDynamicIndexing));
		a_displayer.attribute("shaderStorageImageArrayDynamicIndexing",static_cast<bool>(a_features.shaderStorageImageArrayDynamicIndexing));
		a_displayer.attribute("shaderClipDistance",static_cast<bool>(a_features.shaderClipDistance));
		a_displayer.attribute("shaderCullDistance",static_cast<bool>(a_features.shaderCullDistance));
		a_displayer.attribute("shaderFloat64",static_cast<bool>(a_features.shaderFloat64));
		a_displayer.attribute("shaderInt64",static_cast<bool>(a_features.shaderInt64));
		a_displayer.attribute("shaderInt16",static_cast<bool>(a_features.shaderInt16));
		a_displayer.attribute("shaderResourceResidency",static_cast<bool>(a_features.shaderResourceResidency));
		a_displayer.attribute("shaderResourceMinLod",static_cast<bool>(a_features.shaderResourceMinLod));
		a_displayer.attribute("sparseBinding",static_cast<bool>(a_features.sparseBinding));
		a_displayer.attribute("sparseResidencyBuffer",static_cast<bool>(a_features.sparseResidencyBuffer));
		a_displayer.attribute("sparseResidencyImage2D",static_cast<bool>(a_features.sparseResidencyImage2D));
		a_displayer.attribute("sparseResidencyImage3D",static_cast<bool>(a_features.sparseResidencyImage3D));
		a_displayer.attribute("sparseResidency2Samples",static_cast<bool>(a_features.sparseResidency2Samples));
		a_displayer.attribute("sparseResidency4Samples",static_cast<bool>(a_features.sparseResidency4Samples));
		a_displayer.attribute("sparseResidency8Samples",static_cast<bool>(a_features.sparseResidency8Samples));
		a_displayer.attribute("sparseResidency16Samples",static_cast<bool>(a_features.sparseResidency16Samples));
		a_displayer.attribute("sparseResidencyAliased",static_cast<bool>(a_features.sparseResidencyAliased));
		a_displayer.attribute("variableMultisampleRate",static_cast<bool>(a_features.variableMultisampleRate));
		a_displayer.attribute("inheritedQueries",static_cast<bool>(a_features.inheritedQueries));

		a_displayer.endNode();
	}
	
	void displayDeviceFormats(const std::vector<FormatProperty>& a_format, IDisplayer& a_displayer)
	{
		a_displayer.beginNode("Device Formats properties");
		for (const auto& format : a_format)
		{
			a_displayer.beginNode("Formats");
			a_displayer.attribute("format", to_string(format.format));
			a_displayer.beginNode("Properties");
			a_displayer.attribute("Buffer features", Flag<VkFormatFeatureFlagBits>::to_string(format.properties.bufferFeatures));
			a_displayer.attribute("Linear tiling features", Flag<VkFormatFeatureFlagBits>::to_string(format.properties.linearTilingFeatures));
			a_displayer.attribute("Optimal tiling features", Flag<VkFormatFeatureFlagBits>::to_string(format.properties.optimalTilingFeatures));
			a_displayer.endNode();
			a_displayer.endNode();
		}
		a_displayer.endNode();
	}

	void displayDeviceFormats(const SwapchainCapabilities& a_swapChain, IDisplayer& a_displayer)
	{
		a_displayer.beginNode("Swapchain capabilities");

		a_displayer.beginNode("Surface capabilities");
		a_displayer.attribute("minImageCount", a_swapChain.surfaceCapabilities.minImageCount);
		a_displayer.attribute("maxImageCount", a_swapChain.surfaceCapabilities.maxImageCount);
		a_displayer.attribute("currentExtent.width", a_swapChain.surfaceCapabilities.currentExtent.width);
		a_displayer.attribute("currentExtent.height", a_swapChain.surfaceCapabilities.currentExtent.height);
		a_displayer.attribute("minImageExtent.width", a_swapChain.surfaceCapabilities.minImageExtent.width);
		a_displayer.attribute("minImageExtent.height", a_swapChain.surfaceCapabilities.minImageExtent.height);
		a_displayer.attribute("maxImageExtent.width", a_swapChain.surfaceCapabilities.maxImageExtent.width);
		a_displayer.attribute("maxImageExtent.height", a_swapChain.surfaceCapabilities.maxImageExtent.height);
		a_displayer.attribute("maxImageArrayLayers", a_swapChain.surfaceCapabilities.maxImageArrayLayers);
		a_displayer.attribute("supportedTransforms", Flag<VkSurfaceTransformFlagBitsKHR>::to_string(a_swapChain.surfaceCapabilities.supportedTransforms));
		a_displayer.attribute("currentTransform",to_string(a_swapChain.surfaceCapabilities.currentTransform));
		a_displayer.attribute("supportedCompositeAlpha", Flag< VkCompositeAlphaFlagBitsKHR>::to_string(a_swapChain.surfaceCapabilities.supportedCompositeAlpha));
		a_displayer.attribute("supportedUsageFlags", Flag<VkImageUsageFlagBits>::to_string(a_swapChain.surfaceCapabilities.supportedUsageFlags));
		a_displayer.endNode();

		a_displayer.beginNode("Supported formats");
		for (const auto& format : a_swapChain.supportedFormats)
		{
			a_displayer.beginNode("Format");
			a_displayer.attribute("format", to_string(format.format));
			a_displayer.attribute("color space", to_string(format.colorSpace));
			a_displayer.endNode();
		}
		a_displayer.endNode();

		a_displayer.beginNode("Supported modes");
		for (const auto mode : a_swapChain.supportedModes)
		{
			a_displayer.attribute("mode", to_string(mode));
		}
		a_displayer.endNode();

		a_displayer.endNode();
	}
	//-------------------------------------------------------------------------------

}