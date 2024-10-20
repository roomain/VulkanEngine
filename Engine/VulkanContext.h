#pragma once
/***********************************************
* @headerfile VulkanContext.h
* @date 07 / 10 / 2024
* @author Roomain
************************************************/
#include <vector>
#include <memory>
#include "vulkan/vulkan.h"
#include "VulkanCapabilities.h"
#include "common/notCopiable.h"


struct VulkanParameter;
struct VulkanDeviceParameter;
class VulkanDevice;
using VulkanDevicePtr = std::shared_ptr<VulkanDevice>;

class VulkanContext
{
private:
	static constexpr uint32_t m_appVersion = 1;
	static constexpr uint32_t m_engineVersion = 1;
	static VulkanCapabilities m_capabilities;	/*!< vulkan capabilities*/

	VkInstance m_instance = VK_NULL_HANDLE;		/*!< vulkan instance*/
	std::vector<VulkanDevicePtr> m_vDevices;	/*!< vulkan devices*/

public:
	static VulkanCapabilities& getCapabilities();

	NOT_COPIABLE(VulkanContext)
	VulkanContext() = delete;
	explicit VulkanContext(const VulkanParameter& a_param);
	[[nodiscard]] bool isValid()const noexcept;

	VulkanDevicePtr createNewDevice(const VulkanDeviceParameter& a_param, VkSurfaceKHR a_surface = VK_NULL_HANDLE);
};

