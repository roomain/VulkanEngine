// test_engine.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include "parameters/VulkanParameter.h"
#include "VulkanContext.h"
#include <iostream>
#include <filesystem>

#include "ReflectionManager.h"
#include "EngineWindow.h"
#include "common/string_utils.h"
#include "Capabilities.h"
#include "logger.h"
#include "iLogDisplayer.h"
#include "vulkan_string_to_enum.h"

template<typename Enum> requires std::is_enum_v<Enum>
int convertEnum(const std::string& a_flag)
{
    int flag = 0;
    std::vector<std::string> vValues;
    split(a_flag, '|', vValues);
    for (const auto& val : vValues)
    {
        Enum enumVal;
        to_enum(trim(val), enumVal);
        flag |= static_cast<unsigned int>(enumVal);
    }
    return flag;
}



int deviceChoice(const std::vector<int>&, const VulkanContext*)
{
    return 0;
}

#ifdef USE_SDL
#include "SDL3/SDL.h"
#include "SDL3/SDL_vulkan.h"
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
                //std::cout << "SDL_EVENT_WINDOW_MOVED" << std::endl;
                break;
            case SDL_EVENT_WINDOW_RESIZED:
                //std::cout << "SDL_EVENT_WINDOW_RESIZED" << std::endl;
                break;
            case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
                //std::cout << "SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED" << std::endl;
                break;
            case SDL_EVENT_WINDOW_METAL_VIEW_RESIZED:
                //std::cout << "SDL_EVENT_WINDOW_METAL_VIEW_RESIZED" << std::endl;
                break;
            case SDL_EVENT_WINDOW_MINIMIZED:
                //std::cout << "SDL_EVENT_WINDOW_MINIMIZED" << std::endl;
                break;
            case SDL_EVENT_WINDOW_MAXIMIZED:
                //std::cout << "SDL_EVENT_WINDOW_MAXIMIZED" << std::endl;
                break;
            case SDL_EVENT_WINDOW_RESTORED:
                //std::cout << "SDL_EVENT_WINDOW_RESTORED" << std::endl;
                break;
            case SDL_EVENT_WINDOW_MOUSE_ENTER:
                //std::cout << "SDL_EVENT_WINDOW_MOUSE_ENTER" << std::endl;
                break;
            case  SDL_EVENT_MOUSE_MOTION:
                //std::cout << "SDL_EVENT_MOUSE_MOTION" << std::endl;
                break;
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                //std::cout << "SDL_EVENT_MOUSE_BUTTON_DOWN" << std::endl;
                break;
            case SDL_EVENT_MOUSE_BUTTON_UP:
                //std::cout << "SDL_EVENT_MOUSE_BUTTON_UP" << std::endl;
                break;
            case SDL_EVENT_MOUSE_WHEEL:
                //std::cout << "SDL_EVENT_MOUSE_WHEEL" << std::endl;
                break;
            case SDL_EVENT_MOUSE_ADDED:
                //std::cout << "SDL_EVENT_MOUSE_ADDED" << std::endl;
                break;
            case SDL_EVENT_MOUSE_REMOVED:
                //std::cout << "SDL_EVENT_MOUSE_REMOVED" << std::endl;
                break;
            case SDL_EVENT_WINDOW_MOUSE_LEAVE:
                //std::cout << "SDL_EVENT_WINDOW_MOUSE_LEAVE" << std::endl;
                break;
            case SDL_EVENT_QUIT:
                //std::cout << "SDL_EVENT_QUIT" << std::endl;
                bQuit = true;
                break;
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                //std::cout << "SDL_EVENT_WINDOW_CLOSE_REQUESTED" << std::endl;
                bQuit = true;
                break;
            default:
                //std::cout << "OTHER" << std::endl;
                break;
            }
        }
    }
    return 0;
}

VulkanContext init(VkSurfaceKHR& a_surface, SDL_Window*& a_window)
{
    VulkanParameter engineParam;
    SDL_Init(SDL_INIT_VIDEO);
    a_window = SDL_CreateWindow("TEST_ENGINE", 800, 800, SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);
    SDL_SetWindowTitle(a_window, "Vulkan engine");

    Uint32 extensionCount;
    const char* const* extensionNames = SDL_Vulkan_GetInstanceExtensions(&extensionCount);
    VulkanContext engineCtxt(engineParam, extensionNames, extensionCount);

    SDL_Vulkan_CreateSurface(a_window, engineCtxt.vulkanInstance(), nullptr, &a_surface);

    return engineCtxt;
}

int main()
{
    displayCapabilities();
    auto& deserializer = ReflectionManager::instance();
    ReflectionValue::registerCast<QueueFlag>(&convertEnum<QueueFlag>);
    auto localPath = std::filesystem::current_path();
    deserializer.load(localPath.string() + std::string(R"(\configuration)"), "configuration");


    VkSurfaceKHR surface;
    SDL_Window* window = nullptr;
    VulkanContext engineCtxt(init(surface, window));
    VulkanDeviceParameter devParam;

    VulkanCapabilities& capabilities = VulkanContext::getCapabilities();
    VulkanCapabilities::VulkanDeviceConfMap conf;
    capabilities.findDeviceCompatibleConfiguration(devParam, conf, surface);

    auto device = engineCtxt.createNewDevice(devParam, &deviceChoice, surface);
    //
    int eventRet = eventLoop();
    SDL_Vulkan_DestroySurface(engineCtxt.vulkanInstance(), surface, nullptr);
    return eventRet;
}
#else
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

int eventLoop(GLFWwindow* a_window)
{
    int iRet = 0;
    while (!glfwWindowShouldClose(a_window))
    {
        glfwPollEvents();// get event
        //
    }
    return iRet;
}

class LogDisplayerImpl : public ILogDisplayer
{
protected:
    virtual void intern_process(const LogData& a_logData)
    {
        std::cout << a_logData.message << std::endl;
    }

public:
    using ILogDisplayer::ILogDisplayer;
};


int main()
{
    ILogDisplayerPtr pLogDisplayer = std::make_shared<LogDisplayerImpl>();
    Logger::instance().addLogDisplayer(pLogDisplayer);

    
    auto& deserializer = ReflectionManager::instance();
    ReflectionValue::registerCast<QueueFlag>(&convertEnum<QueueFlag>);
    auto localPath = std::filesystem::current_path();
    deserializer.load(localPath.string() + std::string(R"(\configuration)"), "configuration");


    VulkanDeviceParameter devParam;

    VulkanParameter engineParam;
    // Initialise GLFW
    glfwInit();

    // Set GLFW to NOT work with OpenGL
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "GLFW Vulkan", nullptr, nullptr);

    // get glfw extensions names
    uint32_t glfwExtensionCount = 0;				// GLFW may require multiple extensions
    const char** glfwExtensions;					// Extensions passed as array of cstrings, so need pointer (the array) to pointer (the cstring)

    // Get GLFW extensions
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    VulkanContext engineCtxt(engineParam, glfwExtensions, glfwExtensionCount);
    //glfwCreateWindowSurface(engineCtxt.vulkanInstance(), a_window, nullptr, &a_surface);

    VkSurfaceKHR surface = engineCtxt.createSurface(window);
    displayCapabilities(engineCtxt.capabilities());
 
    auto device = engineCtxt.createNewDevice(devParam, &deviceChoice, surface);
    //
    int eventRet = eventLoop(window);
    glfwDestroyWindow(window);
    glfwTerminate();
    return eventRet;
}
#endif



// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
