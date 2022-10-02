// EngineTester.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "vk_propFun.h"
#include "ConsoleDisplayer.h"
#include "vk_Renderer.h"

//------------------------------------------------------------------------
// GLFW
GLFWwindow* createWindow(std::string wName = "Test Window", const int width = 800, const int height = 600)
{
	// Initialise GLFW
	glfwInit();

	// Set GLFW to NOT work with OpenGL
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	return glfwCreateWindow(width, height, wName.c_str(), nullptr, nullptr);
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

	// create renderer
	Vulkan::ApplicationInfo appInfo{ "Vulkan Engine Tester", 1 };
	Vulkan::RendererProps renderProps{ {} ,{"VK_LAYER_KHRONOS_validation"}};

	// get GLFW vulkan extension required
	uint32_t glfwExtensionCount = 0;
	const char** glfwExt = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	for (uint32_t i = 0; i < glfwExtensionCount; ++i)
		renderProps.instanceProps.push_back(glfwExt[i]);
	renderProps.instanceProps.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);

	Vulkan::VK_Renderer renderer(appInfo, renderProps, nullptr);

	// display instance properties
	displayer.reset();
	Vulkan::displayVulkanCapabilities(renderer.vulkanInstance(), displayer);

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
