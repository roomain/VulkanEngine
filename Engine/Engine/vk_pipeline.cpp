#include "pch.h"
#include "vk_pipeline.h"

namespace Vulkan
{
	VK_Pipeline::VK_Pipeline(const int a_priority) : m_vkPipline{ VK_NULL_HANDLE }, m_vkpipelineLayout{ VK_NULL_HANDLE }, m_priority{ a_priority }
	{
		//
	}

	VK_Pipeline::~VK_Pipeline()
	{
		//
	}

	bool VK_Pipeline::isValid()const noexcept
	{
		bool bRet = false;
		//
		return bRet;
	}

	void VK_Pipeline::destroy(VkDevice a_device)
	{
		if (m_vkPipline != VK_NULL_HANDLE)
			vkDestroyPipeline(a_device, m_vkPipline, nullptr);
		//
	}
}