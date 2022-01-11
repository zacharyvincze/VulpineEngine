#pragma once

#include "Vulpine/vppch.h"

namespace Vulpine {
/**
 * @brief Component for use with objects that require texture rendering.
 *
 */
struct SpriteRenderer {
    std::string texture_path;
    SDL_Rect source_rect;
};

/**
 * @brief Positioning component for 2D objects.
 *
 */
struct Transform {
    SDL_Rect position;
};
}  // namespace Vulpine