#pragma once
#include <type_traits>
#include <memory>
#include <vulkan/vulkan.hpp>
class VulkanPipeline;

/*
 * @brief Defines specific data for a specific category of rendering objects
 */
struct EngineRenderingContext
{
	std::unique_ptr<VulkanPipeline> m_pipeline;	/*!< pipeline for specific object category*/
	bool m_isPipelineBound = false;				/*!< indicate if pipeline is bound in current command buffer*/
};


template<typename Context> requires(std::is_base_of_v<EngineRenderingContext, Context>)
class EngineDrawable
{
	friend class EngineRenderer;

protected:
	static inline Context s_context;

public:
	/*@brief render the object*/
	virtual void render(VkCommandBuffer a_commandBuffer) = 0;
};