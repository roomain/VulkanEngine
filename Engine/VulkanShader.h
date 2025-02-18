#pragma once
/***********************************************
* @headerfile VulkanShader.h
* @date 15 / 02 / 2025
* @author Roomain
************************************************/
#include <string_view>
#include "VulkanObject.h"
#include "VulkanLocalsContexts.h"

/*@brief base class of shader*/
class VulkanShader : public VulkanObject<VulkanDeviceContext>
{
	explicit VulkanShader(const VulkanDeviceContext& a_ctxt);

public:
	bool load(const std::string_view a_filename);
};