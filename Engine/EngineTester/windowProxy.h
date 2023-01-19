#pragma once
#include "vk_WindowSystemProxy.h"
struct GLFWwindow;

/*@brief vulkan window proxy implementation*/
class WindowProxy : public Vulkan::VK_WindowSystemProxy
{
private:
	GLFWwindow* m_pWindow;/*!< pointer on glfw window no ownership*/
	VkSurfaceKHR m_vkSurface = VK_NULL_HANDLE;

public:
	WindowProxy(const VkInstance a_vkInstance, GLFWwindow* const a_window);
	~WindowProxy();

	VkSurfaceKHR surface()override;
	uint32_t width()override;
	uint32_t height()override;
	void resetSurface() override;
};