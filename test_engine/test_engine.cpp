// test_engine.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include "parameters/VulkanParameter.h"
#include "VulkanContext.h"
#include <iostream>
#include <filesystem>
#include "SDL3/SDL.h"
#include "SDL3/SDL_vulkan.h"
//#include "deserialize_functions.h"
#include "EngineWindow.h"
#include "DeserializeManager.h"

int eventLoop()
{
    bool bQuit = false;
    SDL_Event evnt;
    while (!bQuit)
    {
        while (SDL_PollEvent(&evnt) && evnt.type != SDL_EVENT_QUIT)
        {
            switch (evnt.type)
            {
            case SDL_EVENT_WINDOW_MOVED:
                std::cout << "SDL_EVENT_WINDOW_MOVED" << std::endl;
                break;
            case SDL_EVENT_WINDOW_RESIZED:
                std::cout << "SDL_EVENT_WINDOW_RESIZED" << std::endl;
                break;
            case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
                std::cout << "SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED" << std::endl;
                break;
            case SDL_EVENT_WINDOW_METAL_VIEW_RESIZED:
                std::cout << "SDL_EVENT_WINDOW_METAL_VIEW_RESIZED" << std::endl;
                break;
            case SDL_EVENT_WINDOW_MINIMIZED:
                std::cout << "SDL_EVENT_WINDOW_MINIMIZED" << std::endl;
                break;
            case SDL_EVENT_WINDOW_MAXIMIZED:
                std::cout << "SDL_EVENT_WINDOW_MAXIMIZED" << std::endl;
                break;
            case SDL_EVENT_WINDOW_RESTORED:
                std::cout << "SDL_EVENT_WINDOW_RESTORED" << std::endl;
                break;
            case SDL_EVENT_WINDOW_MOUSE_ENTER:
                std::cout << "SDL_EVENT_WINDOW_MOUSE_ENTER" << std::endl;
                break;
            case  SDL_EVENT_MOUSE_MOTION:
                std::cout << "SDL_EVENT_MOUSE_MOTION" << std::endl;
                break;
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                std::cout << "SDL_EVENT_MOUSE_BUTTON_DOWN" << std::endl;
                break;
            case SDL_EVENT_MOUSE_BUTTON_UP:
                std::cout << "SDL_EVENT_MOUSE_BUTTON_UP" << std::endl;
                break;
            case SDL_EVENT_MOUSE_WHEEL:
                std::cout << "SDL_EVENT_MOUSE_WHEEL" << std::endl;
                break;
            case SDL_EVENT_MOUSE_ADDED:
                std::cout << "SDL_EVENT_MOUSE_ADDED" << std::endl;
                break;
            case SDL_EVENT_MOUSE_REMOVED:
                std::cout << "SDL_EVENT_MOUSE_REMOVED" << std::endl;
                break;
            case SDL_EVENT_WINDOW_MOUSE_LEAVE:
                std::cout << "SDL_EVENT_WINDOW_MOUSE_LEAVE" << std::endl;
                break;
            case SDL_EVENT_QUIT:
                std::cout << "SDL_EVENT_QUIT" << std::endl;
                bQuit = true;
                break;
            default:
                std::cout << "OTHER" << std::endl;
                break;
            }
        }
    }
    return 0;
}

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("TEST_ENGINE", 800, 800, SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);
    SDL_SetWindowTitle(window, "TEST");
    //auto curPath = std::filesystem::current_path();
    //curPath = curPath.parent_path().parent_path().append("Reflection/test_files/profiles");
    //DeserializeManager::instance().load(curPath.string(), "profile_unit_test");
    auto& deserializer = DeserializeManager::instance();
    deserializer.load(R"(C:\Projets_GIT\VulkanEngine\test_engine\configuration)", "configuration");
    VulkanParameter engineParam;
    
    VulkanContext engineCtxt(engineParam);
    VkSurfaceKHR surface = VK_NULL_HANDLE;
    SDL_Vulkan_CreateSurface(window, engineCtxt.vulkanInstance(), nullptr, &surface);
    if (surface == VK_NULL_HANDLE)
        std::cout << "ERROR!\n";
    SDL_Vulkan_DestroySurface(engineCtxt.vulkanInstance(), surface, nullptr);

    std::cout << "Hello World!\n";
    return eventLoop();
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
