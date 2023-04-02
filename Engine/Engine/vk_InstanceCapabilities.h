#pragma once

#include <vector>
#include "vulkan/vulkan.h"

namespace Vulkan
{
	class IDataDisplayer;
	class VK_VulkanCapabilities;

	/*@brief contains instance capabilities*/
	class VK_InstanceCapabilities final
	{
		friend class VK_VulkanCapabilities;
	private:
		std::vector<VkLayerProperties> m_layerPops;				/*!< layer properties*/
		std::vector<VkExtensionProperties> m_extensionProps;	/*!< extension properties*/

		VK_InstanceCapabilities();
	public:
		~VK_InstanceCapabilities() = default;
		
		/*@brief display data*/
		void display(IDataDisplayer& a_displayer)const;
		/*@brief check if vulkan instance support layer*/
		[[nodiscard]] bool checkLayer(const std::string& a_layer)const;
		/*@brief check if vulkan instance support layer list*/
		[[nodiscard]] bool checkLayers(const std::vector<std::string>& a_vLayer)const;
		/*@brief check if vulkan instance support extension*/
		[[nodiscard]] bool checkExtension(const std::string& a_ext)const;
		/*@brief check if vulkan instance support extension list*/
		[[nodiscard]] bool checkExtensions(const std::vector<std::string>& a_vExt)const;

	};
}

