#include "pch.h"
#include "vk_check.h"
#include "vk_gets.h"
#include "vk_ext_struct.h"


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

	bool checkPhysicalDeviceForCapabilities(VkPhysicalDevice a_physicalDevice, RendererQueuesConfiguration& a_queueConf, const std::vector<std::string>& a_extension)
	{
		// check extension
		std::vector<VkExtensionProperties> extensions;
		getDeviceExtensions(a_physicalDevice, extensions);

		if(!std::all_of(a_extension.begin(), a_extension.end(), [&](const auto& name)
			{
				return extensions.end() != std::find_if(extensions.begin(), extensions.end(), [&](auto prop)
					{
						return name.compare(prop.extensionName) == 0;
					});
			}))
			return false;

		//------------------------------------------------------------------------------
		a_queueConf.reset();
		// get memory properties
		std::vector<VkQueueFamilyProperties> queuesProperties;
		getQueueFamiliesProperties(a_physicalDevice, queuesProperties);

		// check an feels queues
		int iFamilyIndex = 0;
		for (const auto& queueFamily : queuesProperties)
		{
			if (queueFamily.queueCount > 0)// at least on queue
			{
				for (auto& queueConf : a_queueConf.vQueueConf)
				{
					if (queueConf.type == (queueConf.type & queueFamily.queueFlags))
					{
						queueConf.index = iFamilyIndex;
						break;
					}
				}
			}
			++iFamilyIndex;
		}
		
		return a_queueConf.isValid();
	}
}