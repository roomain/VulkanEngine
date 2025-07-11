// pch.h : Il s'agit d'un fichier d'en-tête précompilé.
// Les fichiers listés ci-dessous sont compilés une seule fois, ce qui améliore les performances de génération des futures builds.
// Cela affecte également les performances d'IntelliSense, notamment la complétion du code et de nombreuses fonctionnalités de navigation du code.
// Toutefois, les fichiers listés ici sont TOUS recompilés si l'un d'entre eux est mis à jour entre les builds.
// N'ajoutez pas de fichiers fréquemment mis à jour ici, car cela annule les gains de performance.

#ifndef PCH_H
#define PCH_H

// ajouter les en-têtes à précompiler ici
#define GLM_ENABLE_EXPERIMENTAL
#include "framework.h"
#include "common/string_utils.h"
#include "common/contains.h"
#include "common/enumerate.h"
#include "LoggingSystem/Exception.h"
#include "VulkanObjects/Vulkan_macros.h"
#include "VulkanObjects/VulkanInitializers.h"
#include "VulkanObjects/VulkanPipelineInitializers.h"
#include "VulkanObjects/VulkanRenderingContext.h"
#include "VulkanObjects/VulkanDefines.h"
#define VMA_VULKAN_VERSION 1003000

#endif //PCH_H
