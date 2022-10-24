#pragma once

#include "Vulpine/Utils/Serializable.h"
#include "Vulpine/vppch.h"

namespace Vulpine {
namespace Components {

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

    std::vector<int> animation;

    // The index pointing to the current source rectangle to be used.
    unsigned int current_frame;

    // The amount of time each frame should spend.
    std::vector<unsigned int> frame_times;

    unsigned int last_update;
};

}  // namespace Components
}  // namespace Vulpine