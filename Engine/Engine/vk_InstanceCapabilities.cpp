#include "pch.h"
#include "vk_InstanceCapabilities.h"
#include "IDataDisplayer.h"

namespace Vulkan
{
	VK_InstanceCapabilities::VK_InstanceCapabilities()
	{
		// get  vulkan instance capabilities
		uint32_t propCount = 0;
		vkEnumerateInstanceLayerProperties(&propCount, nullptr);
		m_layerPops.resize(propCount);
		vkEnumerateInstanceLayerProperties(&propCount, m_layerPops.data());

		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
		m_extensionProps.resize(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, m_extensionProps.data());
	}

	void VK_InstanceCapabilities::display(IDataDisplayer& a_displayer)const
	{
		a_displayer.beginNode("Instance capabilities");
		//--------------------------------------------------------------------------
		a_displayer.beginNode("Instance Layer Properties");
		for (const auto& prop : m_layerPops)
		{
			a_displayer.beginNode(prop.layerName);
			a_displayer.attribute("Description", prop.description);
			a_displayer.attribute("Implementation version", prop.implementationVersion);
			a_displayer.attribute("Specific version", prop.specVersion);
			a_displayer.endNode();
		}
		a_displayer.endNode();
		//--------------------------------------------------------------------------
		a_displayer.beginNode("Instance Extensions");
		for (const auto& extend : m_extensionProps)
		{
			a_displayer.beginNode(extend.extensionName);
			a_displayer.attribute("Specific version", extend.specVersion);
			a_displayer.endNode();
		}
		a_displayer.endNode();
		//--------------------------------------------------------------------------
		a_displayer.endNode();
	}
	
	bool VK_InstanceCapabilities::checkLayer(const std::string& a_layer)const
	{
		return std::any_of(m_layerPops.begin(), m_layerPops.end(),
			[&a_layer](const auto& lay) {return a_layer.compare(lay.layerName) == 0; });
	}

	bool VK_InstanceCapabilities::checkLayers(const std::vector<std::string>& a_vLayer)const
	{
		return !std::any_of(a_vLayer.begin(), a_vLayer.end(), [ this](const auto& layer) {return !checkLayer(layer); });
	}

	bool VK_InstanceCapabilities::checkExtension(const std::string& a_ext)const
	{
		return std::any_of(m_extensionProps.begin(), m_extensionProps.end(),
			[&a_ext](const auto& ext) {return a_ext.compare(ext.extensionName) == 0; });
	}

	bool VK_InstanceCapabilities::checkExtensions( const std::vector<std::string>& a_vExt)const
	{
		return !std::any_of(a_vExt.begin(), a_vExt.end(), [this](const auto& ext) {return !checkExtension(ext); });
	}
}