#pragma once
/***********************************************
* @headerfile VulkanParameter.generated.h
* @date 28/10/2024
* @author reflecGen.py
************************************************/
#include <variant>
#include "DeserializeManager.h"
#include "Deserializer.h"

/* class deserialization macro */
#define _DESERIALIZE_VulkanParameter \
for(const auto&[name, data] : a_serialized) \
{ \
	if(name == "extensions") \
		std::visit(Deserializer<std::vector<std::string>>{ &a_this.extensions }, data); \
	if(name == "layers") \
		std::visit(Deserializer<std::vector<std::string>>{ &a_this.layers }, data); \
}\

/* class deserialization macro */
#define _DESERIALIZE_VulkanQueueFamilyParameter \
for(const auto&[name, data] : a_serialized) \
{ \
	if(name == "bIsRenderer") \
		std::visit(Deserializer<bool>{ &a_this.bIsRenderer }, data); \
	if(name == "flags") \
		std::visit(Deserializer<VkQueueFlags>{ &a_this.flags }, data); \
	if(name == "count") \
		std::visit(Deserializer<uint32_t>{ &a_this.count }, data); \
	if(name == "priority") \
		std::visit(Deserializer<float>{ &a_this.priority }, data); \
}\

/* class deserialization macro */
#define _DESERIALIZE_VulkanDeviceFeatures \
for(const auto&[name, data] : a_serialized) \
{ \
	if(name == "robustBufferAccess") \
		std::visit(Deserializer<bool>{ &a_this.robustBufferAccess }, data); \
	if(name == "fullDrawIndexUint32") \
		std::visit(Deserializer<bool>{ &a_this.fullDrawIndexUint32 }, data); \
	if(name == "imageCubeArray") \
		std::visit(Deserializer<bool>{ &a_this.imageCubeArray }, data); \
	if(name == "independentBlend") \
		std::visit(Deserializer<bool>{ &a_this.independentBlend }, data); \
	if(name == "geometryShader") \
		std::visit(Deserializer<bool>{ &a_this.geometryShader }, data); \
	if(name == "tessellationShader") \
		std::visit(Deserializer<bool>{ &a_this.tessellationShader }, data); \
	if(name == "sampleRateShading") \
		std::visit(Deserializer<bool>{ &a_this.sampleRateShading }, data); \
	if(name == "dualSrcBlend") \
		std::visit(Deserializer<bool>{ &a_this.dualSrcBlend }, data); \
	if(name == "logicOp") \
		std::visit(Deserializer<bool>{ &a_this.logicOp }, data); \
	if(name == "multiDrawIndirect") \
		std::visit(Deserializer<bool>{ &a_this.multiDrawIndirect }, data); \
	if(name == "drawIndirectFirstInstance") \
		std::visit(Deserializer<bool>{ &a_this.drawIndirectFirstInstance }, data); \
	if(name == "depthClamp") \
		std::visit(Deserializer<bool>{ &a_this.depthClamp }, data); \
	if(name == "depthBiasClamp") \
		std::visit(Deserializer<bool>{ &a_this.depthBiasClamp }, data); \
	if(name == "fillModeNonSolid") \
		std::visit(Deserializer<bool>{ &a_this.fillModeNonSolid }, data); \
	if(name == "depthBounds") \
		std::visit(Deserializer<bool>{ &a_this.depthBounds }, data); \
	if(name == "wideLines") \
		std::visit(Deserializer<bool>{ &a_this.wideLines }, data); \
	if(name == "largePoints") \
		std::visit(Deserializer<bool>{ &a_this.largePoints }, data); \
	if(name == "alphaToOne") \
		std::visit(Deserializer<bool>{ &a_this.alphaToOne }, data); \
	if(name == "multiViewport") \
		std::visit(Deserializer<bool>{ &a_this.multiViewport }, data); \
	if(name == "samplerAnisotropy") \
		std::visit(Deserializer<bool>{ &a_this.samplerAnisotropy }, data); \
	if(name == "textureCompressionETC2") \
		std::visit(Deserializer<bool>{ &a_this.textureCompressionETC2 }, data); \
	if(name == "textureCompressionASTC_LDR") \
		std::visit(Deserializer<bool>{ &a_this.textureCompressionASTC_LDR }, data); \
	if(name == "textureCompressionBC") \
		std::visit(Deserializer<bool>{ &a_this.textureCompressionBC }, data); \
	if(name == "occlusionQueryPrecise") \
		std::visit(Deserializer<bool>{ &a_this.occlusionQueryPrecise }, data); \
	if(name == "pipelineStatisticsQuery") \
		std::visit(Deserializer<bool>{ &a_this.pipelineStatisticsQuery }, data); \
	if(name == "vertexPipelineStoresAndAtomics") \
		std::visit(Deserializer<bool>{ &a_this.vertexPipelineStoresAndAtomics }, data); \
	if(name == "fragmentStoresAndAtomics") \
		std::visit(Deserializer<bool>{ &a_this.fragmentStoresAndAtomics }, data); \
	if(name == "shaderTessellationAndGeometryPointSize") \
		std::visit(Deserializer<bool>{ &a_this.shaderTessellationAndGeometryPointSize }, data); \
	if(name == "shaderImageGatherExtended") \
		std::visit(Deserializer<bool>{ &a_this.shaderImageGatherExtended }, data); \
	if(name == "shaderStorageImageExtendedFormats") \
		std::visit(Deserializer<bool>{ &a_this.shaderStorageImageExtendedFormats }, data); \
	if(name == "shaderStorageImageMultisample") \
		std::visit(Deserializer<bool>{ &a_this.shaderStorageImageMultisample }, data); \
	if(name == "shaderStorageImageReadWithoutFormat") \
		std::visit(Deserializer<bool>{ &a_this.shaderStorageImageReadWithoutFormat }, data); \
	if(name == "shaderStorageImageWriteWithoutFormat") \
		std::visit(Deserializer<bool>{ &a_this.shaderStorageImageWriteWithoutFormat }, data); \
	if(name == "shaderUniformBufferArrayDynamicIndexing") \
		std::visit(Deserializer<bool>{ &a_this.shaderUniformBufferArrayDynamicIndexing }, data); \
	if(name == "shaderSampledImageArrayDynamicIndexing") \
		std::visit(Deserializer<bool>{ &a_this.shaderSampledImageArrayDynamicIndexing }, data); \
	if(name == "shaderStorageBufferArrayDynamicIndexing") \
		std::visit(Deserializer<bool>{ &a_this.shaderStorageBufferArrayDynamicIndexing }, data); \
	if(name == "shaderStorageImageArrayDynamicIndexing") \
		std::visit(Deserializer<bool>{ &a_this.shaderStorageImageArrayDynamicIndexing }, data); \
	if(name == "shaderClipDistance") \
		std::visit(Deserializer<bool>{ &a_this.shaderClipDistance }, data); \
	if(name == "shaderCullDistance") \
		std::visit(Deserializer<bool>{ &a_this.shaderCullDistance }, data); \
	if(name == "shaderFloat64") \
		std::visit(Deserializer<bool>{ &a_this.shaderFloat64 }, data); \
	if(name == "shaderInt64") \
		std::visit(Deserializer<bool>{ &a_this.shaderInt64 }, data); \
	if(name == "shaderInt16") \
		std::visit(Deserializer<bool>{ &a_this.shaderInt16 }, data); \
	if(name == "shaderResourceResidency") \
		std::visit(Deserializer<bool>{ &a_this.shaderResourceResidency }, data); \
	if(name == "shaderResourceMinLod") \
		std::visit(Deserializer<bool>{ &a_this.shaderResourceMinLod }, data); \
	if(name == "sparseBinding") \
		std::visit(Deserializer<bool>{ &a_this.sparseBinding }, data); \
	if(name == "sparseResidencyBuffer") \
		std::visit(Deserializer<bool>{ &a_this.sparseResidencyBuffer }, data); \
	if(name == "sparseResidencyImage2D") \
		std::visit(Deserializer<bool>{ &a_this.sparseResidencyImage2D }, data); \
	if(name == "sparseResidencyImage3D") \
		std::visit(Deserializer<bool>{ &a_this.sparseResidencyImage3D }, data); \
	if(name == "sparseResidency2Samples") \
		std::visit(Deserializer<bool>{ &a_this.sparseResidency2Samples }, data); \
	if(name == "sparseResidency4Samples") \
		std::visit(Deserializer<bool>{ &a_this.sparseResidency4Samples }, data); \
	if(name == "sparseResidency8Samples") \
		std::visit(Deserializer<bool>{ &a_this.sparseResidency8Samples }, data); \
	if(name == "sparseResidency16Samples") \
		std::visit(Deserializer<bool>{ &a_this.sparseResidency16Samples }, data); \
	if(name == "sparseResidencyAliased") \
		std::visit(Deserializer<bool>{ &a_this.sparseResidencyAliased }, data); \
	if(name == "variableMultisampleRate") \
		std::visit(Deserializer<bool>{ &a_this.variableMultisampleRate }, data); \
	if(name == "inheritedQueries") \
		std::visit(Deserializer<bool>{ &a_this.inheritedQueries }, data); \
}\

/* class deserialization macro */
#define _DESERIALIZE_VulkanDeviceParameter \
for(const auto&[name, data] : a_serialized) \
{ \
	if(name == "extensions") \
		std::visit(Deserializer<std::vector<std::string>>{ &a_this.extensions }, data); \
	if(name == "layers") \
		std::visit(Deserializer<std::vector<std::string>>{ &a_this.layers }, data); \
	if(name == "queues") \
		std::visit(Deserializer<std::vector<VulkanQueueFamilyParameter>>{ &a_this.queues }, data); \
	if(name == "features") \
		std::visit(Deserializer<VulkanDeviceFeatures>{ &a_this.features }, data); \
}\

