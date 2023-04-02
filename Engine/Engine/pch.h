// pch.h : Il s'agit d'un fichier d'en-tête précompilé.
// Les fichiers listés ci-dessous sont compilés une seule fois, ce qui améliore les performances de génération des futures builds.
// Cela affecte également les performances d'IntelliSense, notamment la complétion du code et de nombreuses fonctionnalités de navigation du code.
// Toutefois, les fichiers listés ici sont TOUS recompilés si l'un d'entre eux est mis à jour entre les builds.
// N'ajoutez pas de fichiers fréquemment mis à jour ici, car cela annule les gains de performance.

#ifndef PCH_H
#define PCH_H

// ajouter les en-têtes à précompiler ici
//#include "framework.h"
#include "vulkan/vulkan.h"
#include "vk_application.h"
#include "vk_images.h"
#include "vk_buffers.h"
#include "vk_VulkanCapabilities.h"
#include "vk_macros.h"
#include "vk_struct_initializers.h"
#include "vk_files.h"
#include "vk_Exception.h"
#include "vk_macros.h"

#endif //PCH_H
