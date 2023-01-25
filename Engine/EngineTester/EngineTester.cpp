// EngineTester.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "ConsoleDisplayer.h"
#include "vk_Renderer.h"
#include <filesystem>
#include "windowProxy.h"
#include "vk_Exception.h"
#include "vk_configuration.h"
#include "vk_application.h"

//------------------------------------------------------------------------
// GLFW
GLFWwindow* createWindow(const std::string& wName = "Test Window", const int width = 800, const int height = 600)
{
	// Initialise GLFW
	glfwInit();

	// Set GLFW to NOT work with OpenGL
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	return glfwCreateWindow(width, height, wName.c_str(), nullptr, nullptr);
}

[[nodiscard]] int chooseDevice(const std::vector<Vulkan::DeviceInfo>& a_CompatibleDevices)
{
	int iDev = -1;

	int iSize = static_cast<int>(a_CompatibleDevices.size());
	do
	{
		std::cout << "Choose device:" << std::endl;
		int iIndex = 0;
		for (const auto& dev : a_CompatibleDevices)
		{
			std::cout << "\t" << iIndex << " - " << dev.name << std::endl;
			++iIndex;
		}

		std::cout << "choose: ";
		std::cin >> iDev;
		std::cout << std::endl;
	} while (iDev >= iSize);

	return iDev >= 0 ? a_CompatibleDevices[iDev].deviceIndex : -1;
}


//------------------------------------------------------------------------

int main(const int a_argc, const char** a_argv)
{
	// create GLFW window
	GLFWwindow* pGLFW_window = createWindow("Vulkan Engine Tester", 800, 600);

	// display vulkan capabilities
	ConsoleDisplayer displayer;
	Vulkan::VK_Application* const pVkApp = Vulkan::VK_Application::instance();
	pVkApp->displayInstanceCapabilities(displayer);


	std::filesystem::path execPath(a_argv[0]);
	auto parentPath = execPath.parent_path();

	// GET GLFW EXTENSIONS FOR VULKAN
	// Set up extensions Instance will use
	uint32_t glfwExtensionCount = 0;				// GLFW may require multiple extensions
	const char** glfwExtensions;					// Extensions passed as array of cstrings, so need pointer (the array) to pointer (the cstring)

	// Get GLFW extensions
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	std::vector<std::string> glfwVulkanExt;
	for (uint32_t i = 0; i < glfwExtensionCount; ++i)
		glfwVulkanExt.emplace_back(glfwExtensions[i]);
	//------------------------------------------------------------------------------------------------------------------------------------------------
	std::shared_ptr<WindowProxy> pWindowProxy;
	ConsoleLogger logger;
	std::string vkConfFile = parentPath.string() + R"(\Conf\configuration.xml)";
	std::shared_ptr<Vulkan::VK_Renderer> pRenderer;
	try
	{
		Vulkan::VulkanConfiguration vkConf;
		Vulkan::loadConfiguration(vkConfFile, vkConf);

		// get glfw extensions names
		uint32_t glfwExtensionCount = 0;				// GLFW may require multiple extensions
		const char** glfwExtensions;					// Extensions passed as array of cstrings, so need pointer (the array) to pointer (the cstring)

		// Get GLFW extensions
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		// Add GLFW extensions to list of extensions
		for (size_t i = 0; i < glfwExtensionCount; i++)
		{
			vkConf.instanceExtProps.push_back(glfwExtensions[i]);
		}

		if (pVkApp->checkInstanceExtensions(vkConf.instanceExtProps) && pVkApp->checkInstanceLayers(vkConf.instanceLayers))
		{
			// create vulkan instance
			pVkApp->createVulkanInstance(vkConf, &logger);
			pVkApp->displayDevicesCapabilities(displayer);

			pWindowProxy = std::make_shared<WindowProxy>(pVkApp->vulkanInstance(), pGLFW_window);
			std::vector<Vulkan::DeviceInfo> compatibleDeviceList;
			pVkApp->searchCompatibleDevice(vkConf, compatibleDeviceList, pWindowProxy);
			
			if (compatibleDeviceList.empty())
			{
				std::cerr << "No compatible device found." << std::endl;
			}
			else
			{
				int devIndex = chooseDevice(compatibleDeviceList);
				if (devIndex >= 0)
				{
					pRenderer = pVkApp->createRenderer(vkConf, compatibleDeviceList[devIndex], pWindowProxy);
				}
				else
				{
					std::cout << "No device chosen." << std::endl;
				}
			}
		}
		else
		{
			std::cerr << "Some instance extensions and/or instance layers are not supported." << std::endl;
		}
	}
	catch (Vulkan::VK_Exception& except)
	{
		std::cerr << except.what() << std::endl;
	}
	catch (std::exception& except)
	{
		std::cerr << except.what() << std::endl;
	}

	/*Vulkan::VK_Renderer renderer;
	try
	{
		std::vector<Vulkan::PhysicalDeviceInfo> vCompatibleDevices;
		renderer.init(parentPath.string() + R"(\Conf\configuration.xml)", &logger, glfwVulkanExt, vCompatibleDevices);

		displayer.reset();
		for (const auto& dev : vCompatibleDevices)
			displayDeviceCapabilities(renderer.vulkanInstance(), dev.index, displayer);

		int index = chooseDevice(vCompatibleDevices);
		if(index >= 0)
			renderer.startRendering(index, std::make_unique<WindowProxy>(renderer.vulkanInstance(), pGLFW_window));
	}
	catch (Vulkan::VK_Exception& except)
	{
		std::cerr << except.what();
	}
	catch (std::exception& except)
	{
		std::cerr << except.what();
	}*/


	// GLFW loop
	while (!glfwWindowShouldClose(pGLFW_window))
	{
		glfwPollEvents();// get event
		//
	}

	// release window
	glfwDestroyWindow(pGLFW_window);
	glfwTerminate();

	std::cout << "Application ended!" << std::endl;
	return 0;
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
