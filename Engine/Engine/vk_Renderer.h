#pragma once
#include <string>
#include <vector>
#include <memory>

#include "vk_files.h"
#include "vk_images.h"
#include "vk_globals.h"
#include "vk_pipeline.h"
#include "vk_device.h"
#include "vk_configuration.h"

#pragma warning(push)
#pragma warning( disable : 4251)

namespace Vulkan
{
	class VK_WindowSystemProxy;
	struct SwapchainCapabilities;

	struct RenderDeviceConf
	{
		bool useDepthBuffer;					/*!< flag use depth buffer*/
		uint64_t frameTimeout;					/*!< max frame acquire time*/
		VkInstance vkInstance;					/*!< vulkan instance*/
		DeviceQueuesConfiguration queueConf;	/*!< queue configuration*/
	};

	/*@brief vulkan renderer*/
	class ENGINE_EXPORT VK_Renderer : public VK_Device
	{
	private:
		void createSwapChain();
		void destroySwapChain();

	public:
		[[nodiscard]] explicit VK_Renderer(const uint32_t a_deviceIndex, RenderDeviceConf&& a_rendererConf,
			const std::vector<std::string>& a_deviceExt, const std::shared_ptr<VK_WindowSystemProxy>& a_pWwinProxy);

		VK_Renderer(const VK_Renderer&) = delete;
		VK_Renderer() = delete;
		virtual ~VK_Renderer();
		VK_Renderer& operator = (const VK_Renderer&) = delete;

		/*@brief called when window is resized*/
		void onWindowResized();

		/*@brief render on screen frame*/
		bool renderOnScreen();

		/*@brief render offscreen*/
		bool renderOffScreen();

		/*@brief create frame buffer*/
		//void createFramebuffer();

	private:
		RenderDeviceConf m_RendererConf;					/*!< renderer configuration*/
		VkQueue m_graphicsQueue;							/*!< graphics operations queue*/
		VkQueue m_presentationQueue;						/*!< presentation queue*/

		// TODO more queues (store and use in a rendering module)

		VkSwapchainKHR m_swapChain;								/*!< swapchain*/
		std::vector<BaseImage> m_vSwapchainImages;				/*!< swapchain images*/
		ImagePool m_depthImagesPool;							/*!< depth images*/
		//--------------------------------------------------------------------------------------------
		//Synchronisation
		VkFence m_acquireFence;									/*!< acquire fence*/
		std::vector<VkSemaphore> m_vPresentSemaphore;			/*!< presentation synchronisation*/
		std::vector<VkSemaphore> m_vAcquireSemaphore;			/*!< acquire synchronisation*/
		uint32_t m_renderingIndex = 0;							/*!< index of current synchronisation*/

		std::shared_ptr<VK_WindowSystemProxy> m_pWindowProxy;	/*!< proxy to window system*/

		
		/*@brief destroy presentation and acquire semaphore*/
		void destroySemaphores();
		/*@brief create presentation and acquire  semaphore*/
		void createSemaphores();
		/*@brief reset presentation and acquire  semaphore*/
		void resetSemaphores();
		/*@brief release the entire vulkan resources, devices and instace*/
		void release();
		/*@brief destroy all depthbuffer images and associated memory*/
		void destroyDepthBufferImages();
		/*@brief creates depthbuffer images and associated memory*/
		void createDepthBufferImages();
		/*@brief find best format for an image*/
		[[nodiscard]] VkFormat findBestImageFormat(const std::vector<VkFormat>& a_preferedFormats, const VkImageTiling a_preferedTiling, const VkFormatFeatureFlags a_preferedFlags);
	};
}

#pragma warning(pop)
