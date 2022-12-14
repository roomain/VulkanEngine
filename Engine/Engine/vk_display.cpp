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

	void displayDeviceExtensions(VkPhysicalDevice a_physicalDevice, IDisplayer& a_displayer)
	{
		std::vector<VkExtensionProperties> extensions;
		getDeviceExtensions(a_physicalDevice, extensions);
		a_displayer.beginNode("Device Extensions");
		for(const auto& ext : extensions)
			a_displayer.attribute(std::string(ext.extensionName), ext.specVersion);
		a_displayer.endNode();
	}

	void displayQueuesProps(VkPhysicalDevice a_physicalDevice, IDisplayer& a_displayer)
	{
		a_displayer.beginNode("Queues");
		std::vector<VkQueueFamilyProperties> vFamilies;
		getQueueFamiliesProperties(a_physicalDevice, vFamilies);
		for (const auto& familyProp : vFamilies)
		{
			a_displayer.beginNode("Queue");
			a_displayer.attribute("count", familyProp.queueCount);
			a_displayer.attribute("deviceID", Flag<VkQueueFlagBits>::to_string(familyProp.queueFlags));
			a_displayer.attribute("image granularity width", familyProp.minImageTransferGranularity.width);
			a_displayer.attribute("image granularity height", familyProp.minImageTransferGranularity.height);
			a_displayer.attribute("image granularity depth", familyProp.minImageTransferGranularity.depth);
			a_displayer.endNode();
		}
		a_displayer.endNode();
	}

	void displayDeviceCapabilities(VkPhysicalDevice a_physicalDevice, IDisplayer& a_displayer)
	{
		VkPhysicalDeviceProperties devProp;
		vkGetPhysicalDeviceProperties(a_physicalDevice, &devProp);
		a_displayer.beginNode("Physical Device");
		a_displayer.attribute("apiVersion", static_cast<unsigned int>(devProp.apiVersion));
		a_displayer.attribute("driverVersion", static_cast<unsigned int>(devProp.driverVersion));
		a_displayer.attribute("vendorID", static_cast<unsigned int>(devProp.vendorID));
		a_displayer.attribute("deviceID", static_cast<unsigned int>(devProp.deviceID));
		a_displayer.attribute("deviceType", to_string(devProp.deviceType));
		a_displayer.attribute("deviceName", devProp.deviceName);

		std::string strData;
		for (auto digit : devProp.pipelineCacheUUID)
			strData += std::to_string(digit);

		a_displayer.attribute("pipelineCacheUUID", strData);
		displayDeviceLimits(devProp.limits, a_displayer);
		displayDeviceSparseProps(devProp.sparseProperties, a_displayer);
		displayQueuesProps(a_physicalDevice, a_displayer);
		displayDeviceExtensions(a_physicalDevice, a_displayer);
		a_displayer.endNode();
	}

	//-------------------------------------------------------------------------------
	void displayInstanceLayerProps(IDisplayer& a_displayer)
	{
		std::vector<VkLayerProperties> vLayerProp;
		getInstanceLayerProps(vLayerProp);

		a_displayer.beginNode("Instance Layer Properties");
		for (const auto& prop : vLayerProp)
		{
			a_displayer.beginNode(prop.layerName);
			a_displayer.attribute("Description", prop.description);
			a_displayer.attribute("Implementation version", prop.implementationVersion);
			a_displayer.attribute("Specific version", prop.specVersion);
			a_displayer.endNode();
		}
		a_displayer.endNode();
	}

	void displayInstanceExtensionProps(IDisplayer& a_displayer)
	{
		std::vector<VkExtensionProperties> vProperties;
		getInstanceExtProps(vProperties);

		a_displayer.beginNode("Instance Extensions");
		for (const auto& extend : vProperties)
		{
			a_displayer.beginNode(extend.extensionName);
			a_displayer.attribute("Specific version", extend.specVersion);
			a_displayer.endNode();
		}
		a_displayer.endNode();
	}

	void displayVulkanCapabilities(VkInstance a_vulkan, IDisplayer& a_displayer)
	{
		uint32_t uiDeviceCount = 0;
		VK_CHECK(vkEnumeratePhysicalDevices(a_vulkan, &uiDeviceCount, nullptr));
		if (uiDeviceCount > 0)
		{
			std::vector<VkPhysicalDevice> physicalDevices(static_cast<size_t>(uiDeviceCount));
			VK_CHECK(vkEnumeratePhysicalDevices(a_vulkan, &uiDeviceCount, physicalDevices.data()));

			for (auto dev : physicalDevices)
				displayDeviceCapabilities(dev, a_displayer);
		}
	}

	void displayDeviceCapabilities(VkInstance a_vulkan, const int a_deviceIndex, IDisplayer& a_displayer)
	{
		uint32_t uiDeviceCount = 0;
		VK_CHECK(vkEnumeratePhysicalDevices(a_vulkan, &uiDeviceCount, nullptr));
		if (uiDeviceCount > 0)
		{
			std::vector<VkPhysicalDevice> physicalDevices(static_cast<size_t>(uiDeviceCount));
			VK_CHECK(vkEnumeratePhysicalDevices(a_vulkan, &uiDeviceCount, physicalDevices.data()));

			if(a_deviceIndex >= 0 && a_deviceIndex < physicalDevices.size())
				displayDeviceCapabilities(physicalDevices[a_deviceIndex], a_displayer);
		}
	}
}