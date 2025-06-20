#pragma once
#include <memory>
#include <vulkan/vulkan.hpp>
class VulkanPipeline;

/*
 * @brief Defines specific data for a specific category of rendering objects
 */
struct EngineRenderingContext
{
	std::unique_ptr<VulkanPipeline> m_pipeline;	/*!< pipeline for specific object category*/
};
