#pragma once

# if defined(ENTITIES_EXPORTS)
#  define ENTITIES_EXPORT __declspec(dllexport)
# else
#  define ENTITIES_EXPORT __declspec(dllimport)
# endif