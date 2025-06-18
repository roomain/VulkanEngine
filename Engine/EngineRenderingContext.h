#pragma once
#include <memory>

class VulkanPipeline;

/*
 * @brief Defines specific data for a specific category of rendering objects
 */
class EngineRenderingContext
{
protected:
	std::unique_ptr<VulkanPipeline> m_pipeline;	/*!< pipeline for specific object category*/

	/*todo*/
};
