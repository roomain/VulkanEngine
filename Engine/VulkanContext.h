#pragma once
/***********************************************
* @headerfile VulkanContext.h
* @date 07 / 10 / 2024
* @author Roomain
************************************************/
#include <vector>
#include <memory>
#include <functional>
#include "vulkan/vulkan.h"
#include "Capabilities/VulkanCapabilities.h"
#include "common/notCopiable.h"
#include "Engine_globals.h"


#pragma warning(push)
#pragma warning( disable : 4251 )

struct VulkanParameter;
struct VulkanDeviceParameter;
struct VulkanDeviceContext;
class VulkanDevice;
using VulkanDevicePtr = std::shared_ptr<VulkanDevice>;
class VulkanContext;

/*@brief callback to choose device : get index of compatible device, return the chosen device*/
using DeviceChoice = std::function<int(const std::vector<int>&, const VulkanContext*)>;

class VULKAN_ENGINE_LIB VulkanContext : public std::enable_shared_from_this<VulkanContext>
{
private:
	static constexpr uint32_t m_appVersion = 1;
	static constexpr uint32_t m_engineVersion = 1;
	std::shared_ptr<VulkanCapabilities> m_capabilities;
	VkInstance m_instance = VK_NULL_HANDLE;		/*!< vulkan instance*/
	std::vector<VulkanDevicePtr> m_vDevices;	/*!< vulkan devices*/

public:
	explicit VulkanContext(const VulkanParameter& a_param, const char* const* a_extraExtension = nullptr, const int a_numExt = 0);
	VulkanContext(VulkanContext&&) noexcept = default;
	VulkanContext& operator = (VulkanContext&&) noexcept = default;
	NOT_COPIABLE(VulkanContext)
	VulkanContext() = delete;
	[[nodiscard]] bool isValid()const noexcept;
	[[nodiscard]] VkInstance vulkanInstance()const noexcept { return m_instance; }
	[[nodiscard]] VkSurfaceKHR createSurface(void* a_platformWindow)const;
	[[nodiscard]] VulkanDevicePtr createNewDevice(const VulkanDeviceParameter& a_param, const DeviceChoice& a_choose, VkSurfaceKHR a_surface = VK_NULL_HANDLE);
	[[nodiscard]] std::shared_ptr<VulkanCapabilities> capabilities()const noexcept { return m_capabilities; }
};


#pragma warning(pop)