#pragma once
/***********************************************
* @headerfile Engine_globals.h
* @date 24 / 10 / 2024
* @author Roomain
************************************************/

#ifdef VULKAN_ENGINE_EXPORT
#define VULKAN_ENGINE_LIB __declspec(dllexport)
#else
#define VULKAN_ENGINE_LIB __declspec(dllimport)
#endif
