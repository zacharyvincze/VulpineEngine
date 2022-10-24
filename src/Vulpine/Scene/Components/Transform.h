#pragma once

#include "Vulpine/Utils/Serializable.h"
#include "Vulpine/vppch.h"

namespace Vulpine {
namespace Components {
/**
 * @brief Positioning component for 2D objects.
 *
 */
struct Transform {
    SDL_Rect position;
};
}  // namespace Components
}  // namespace Vulpine