// EngineTester.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "vk_display.h"
#include "vk_enumerate.h"
#include "ConsoleDisplayer.h"
#include "vk_Renderer.h"
#include <filesystem>


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

bool chooseDevice(const Vulkan::VK_Renderer& a_renderer)
{
	int iDev = -1;

	std::vector<Vulkan::DeviceInfo> vdevices;
	Vulkan::enumerateDevicesInfo(a_renderer.vulkanInstance(), vdevices);

	int iSize = static_cast<int>(vdevices.size());
	do
	{
		std::cout << "Choose device:" << std::endl;
		int iIndex = 0;
		for (const auto& dev : vdevices)
		{
			std::cout << "\t" << iIndex << " - " << dev.deviceName << std::endl;
			++iIndex;
		}

		std::cout << "choose: ";
		std::cin >> iDev;
		std::cout << std::endl;
	} while (iDev >= iSize);

	// TODO

	return iDev > 0;
}


//------------------------------------------------------------------------

int main(const int a_argc, const char** a_argv)
{
	// create GLFW window
	GLFWwindow* pGLFW_window = createWindow("Vulkan Engine Tester", 800, 600);

	// display vulkan capabilities
	ConsoleDisplayer displayer;
	Vulkan::displayInstanceLayerProps(displayer);
	Vulkan::displayInstanceExtensionProps(displayer);


	std::filesystem::path execPath(a_argv[0]);
	auto parentPath = execPath.parent_path();

	Vulkan::VK_Renderer renderer(parentPath.string() + R"(\Conf\configuration.xml)", nullptr);

	// display instance properties
	displayer.reset();
	Vulkan::displayVulkanCapabilities(renderer.vulkanInstance(), displayer);
	if (!chooseDevice(renderer))
		return 0;


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
