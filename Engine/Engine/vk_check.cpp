#include "pch.h"
#include "vk_check.h"


namespace Vulkan
{
	bool checkInstanceLayerProps(const std::vector<const char*>& a_properties)
	{
		bool bRet = true;
		std::vector<VkLayerProperties> vLayerProp;
		getInstanceLayerProps(vLayerProp);
		for (auto& prop : a_properties)
		{
			std::string strProp = prop;
			if (vLayerProp.end() == std::find_if(vLayerProp.begin(), vLayerProp.end(), [&](auto layer)
				{
					return strProp.compare(layer.layerName) == 0;
				}))
				return false;

				
		}
		return bRet;
	}

	bool checkInstanceExtensionProps(const std::vector<const char*>& a_properties, bool& a_hasDebugExt)
	{
		bool bRet = true;
		a_hasDebugExt = false;
		std::vector<VkExtensionProperties> vProperties;
		getInstanceExtProps(vProperties);

		for (auto& prop : a_properties)
		{
			std::string strProp = prop;
			if (vProperties.end() == std::find_if(vProperties.begin(), vProperties.end(), [&](auto curProp)
				{
					return strProp.compare(curProp.extensionName) == 0;
				}))
				return false;

			if (strProp.compare(VK_EXT_DEBUG_REPORT_EXTENSION_NAME) == 0)
				a_hasDebugExt = true;
		}
		return bRet;
	}

}