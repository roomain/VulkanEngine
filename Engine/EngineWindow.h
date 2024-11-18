#pragma once
/***********************************************
* @headerfile EngineWindow.h
* @date 27 / 10 / 2024
* @author Roomain
************************************************/
#include <memory>
#include <functional>
#include "EngineResizable.h"
#include "vulkan/vulkan.hpp"

#pragma warning(push)
#pragma warning( disable : 4251 )

class VulkanDevice;
class VulkanContext;
struct EngineResizeEvent;
struct EngineMouseEvent;
struct EngineCloseEvent;


/*@brief base class for windows encapsulates the external windows library*/
class VULKAN_ENGINE_LIB EngineWindow : public EngineResizable
{
protected:
	VkSurfaceKHR m_surface;                         /*!< vulkan window surface*/
    std::shared_ptr<VulkanDevice> m_device;         /*!< device associated to this window*/

    virtual void createSurface() = 0;
    virtual void destroySurface() = 0;

public:
    EngineWindow(VulkanContext& a_ctx);
    virtual ~EngineWindow();
    // ctor with callback create/ destroy surface
    inline [[nodiscard]] VkSurfaceKHR surface()const { return m_surface; };	/*!< get rendering surface*/
    std::shared_ptr<VulkanDevice> device()const noexcept { return m_device; }
    virtual uint32_t width() = 0;		                                    /*!< get window width*/
    virtual uint32_t height() = 0;		                                    /*!< get window height*/
    virtual void onResizeEvent(EngineResizeEvent& a_events) = 0;
    virtual void onMouseEvent(EngineMouseEvent& a_event) = 0;
    virtual void onCloseEvent(EngineCloseEvent& a_event) = 0;
};


#pragma warning(pop)