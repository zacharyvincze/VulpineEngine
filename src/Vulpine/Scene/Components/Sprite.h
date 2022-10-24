#pragma once

#include "Vulpine/Utils/Serializable.h"
#include "Vulpine/vppch.h"

namespace Vulpine {
namespace Components {

/**
 * @brief Component for use with objects that require texture rendering.
 * This should be used alongside the transform component to ensure that there
 * is a destination rectangle.
 *
 */
struct Sprite {
    std::string texture_path;
    SDL_Rect source_rect;
};

}  // namespace Components
}  // namespace Vulpine