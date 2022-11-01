#include "pch.h"


namespace Vulkan
{
	bool checkInstanceLayerProps(const std::vector<const char*>& a_properties)
	{
		std::vector<VkLayerProperties> vLayerProp;
		getInstanceLayerProps(vLayerProp);
		bool bRet = std::all_of(a_properties.begin(), a_properties.end(), [&](const auto& name)
			{
				return vLayerProp.end() != std::find_if(vLayerProp.begin(), vLayerProp.end(), [&](auto layer)
					{
						return strcmp(name, layer.layerName) == 0;
					});
			});
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

	bool checkInstanceLayerProps(const std::vector<std::string>& a_layers)
	{
		bool bRet = true;
		std::vector<VkLayerProperties> vLayerProp;
		getInstanceLayerProps(vLayerProp);
		for (auto& strProp : a_layers)
		{
			if (vLayerProp.end() == std::find_if(vLayerProp.begin(), vLayerProp.end(), [&](auto layer)
				{
					return strProp.compare(layer.layerName) == 0;
				}))
				return false;


		}
		return bRet;
	}

	bool checkInstanceExtensionProps(const std::vector<std::string>& a_properties, bool& a_hasDebugExt)
	{
		bool bRet = true;
		a_hasDebugExt = false;
		std::vector<VkExtensionProperties> vProperties;
		getInstanceExtProps(vProperties);

		for (auto& strProp : a_properties)
		{
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

	bool checkPhysicalDeviceExtension(VkPhysicalDevice a_physicalDevice, const std::vector<std::string>& a_extension)
	{
		std::vector<VkExtensionProperties> extensions;
		getDeviceExtensions(a_physicalDevice, extensions);
		return std::all_of(a_extension.begin(), a_extension.end(), [&](const auto& name)
			{
				return extensions.end() != std::find_if(extensions.begin(), extensions.end(), [&](auto prop)
					{
						return name.compare(prop.extensionName) == 0;
					});
			});
	}

	bool checkPhysicalDeviceQueues(VkPhysicalDevice a_physicalDevice, RendererQueuesConfiguration& a_queueConf)
	{
		getDeviceQueues(a_physicalDevice, a_queueConf);
		return a_queueConf.isValid();
	}
}