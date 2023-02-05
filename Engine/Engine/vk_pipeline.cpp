#include "pch.h"
#include "vk_pipeline.h"
#include "vk_device.h"

namespace Vulkan
{
	VK_Pipeline::VK_Pipeline(std::shared_ptr<VK_Device>& a_pDevice, const int a_priority, std::shared_ptr<VK_Shader>& a_pShader) : 
		VK_Object{ a_pDevice }, m_vkPipline{ VK_NULL_HANDLE },
		m_vkpipelineLayout{ VK_NULL_HANDLE }, m_priority{ a_priority }, m_pShader{ a_pShader }
	{
		//
	}

	VK_Pipeline::~VK_Pipeline()
	{
		destroy();
	}

	bool VK_Pipeline::isValid()const noexcept
	{
		bool bRet = false;
		//
		return bRet;
	}

	void VK_Pipeline::destroy()
	{
		auto pDevice = m_vkDevice.lock();
		if (pDevice && pDevice->vulkanDevice().logicalDevice != VK_NULL_HANDLE)
			vkDestroyPipeline(pDevice->vulkanDevice().logicalDevice, m_vkPipline, nullptr);
		//
	}
}