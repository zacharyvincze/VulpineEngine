#pragma once

#include "Vulpine/vppch.h"

namespace Vulpine {
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

/**
 * @brief Positioning component for 2D objects.
 *
 */
struct Transform {
    SDL_Rect position;
};

/**
 * @brief Component for use with sprites that have multiple frames.
 * Includes timing for each frame and the corresponding rectangles
 * required for each frame.
 *
 * Note that this must be used with the sprite component (which contains the
 * texture alongside the position)
 *
 */
struct AnimatedSprite {
    // Source rectangles that correspond to each frame.
    std::vector<SDL_Rect> frames;

    // The index pointing to the current source rectangle to be used.
    unsigned int current_frame;

    // The amount of time each frame should spend.
    unsigned int frame_time;
};

}  // namespace Vulpine