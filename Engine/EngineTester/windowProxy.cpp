#include "windowProxy.h"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "vk_macros.h"

WindowProxy::WindowProxy(const VkInstance a_vkInstance, GLFWwindow* const a_window) : m_pWindow{a_window}
{
	VK_CHECK(glfwCreateWindowSurface(a_vkInstance, m_pWindow, nullptr, &m_vkSurface))
}

WindowProxy::~WindowProxy()
{
	//
}

VkSurfaceKHR WindowProxy::surface()
{
	return m_vkSurface;
}

uint32_t WindowProxy::width()
{
	int width = 0;
	glfwGetWindowSize(m_pWindow, &width, nullptr);
	return static_cast<uint32_t>(width);
}

uint32_t WindowProxy::height()
{
	int height = 0;
	glfwGetWindowSize(m_pWindow, nullptr, &height);
	return static_cast<uint32_t>(height);
}