#pragma once
/***********************************************
* @headerfile EngineWindow.h
* @date 27 / 10 / 2024
* @author Roomain
************************************************/
#include <memory>
#include "EngineResizable.h"
#include "vulkan/vulkan.hpp"
#include "VulkanDevice.h"

#pragma warning(push)
#pragma warning( disable : 4251 )
/*@brief base class for windows encapsulates the external windows library*/
class VULKAN_ENGINE_LIB EngineWindow : public EngineResizable
{
protected:
	VkSurfaceKHR m_surface;                         /*!< vulkan window surface*/
    std::shared_ptr<VulkanDevice> m_device;         /*!< device associated to this window*/

public:
    inline [[nodiscard]] VkSurfaceKHR surface()const { return m_surface; };	/*!< get rendering surface*/
    virtual void resetSurface() = 0;	                                    /*!< reset surface handle*/
    std::shared_ptr<VulkanDevice> device()const noexcept;
};
#pragma warning(pop)