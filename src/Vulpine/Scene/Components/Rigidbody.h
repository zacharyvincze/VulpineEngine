#pragma once

#include "Vulpine/Core/DataStructures/Vector.h"
#include "Vulpine/vppch.h"

namespace Vulpine {
namespace Components {

/**
 * @brief Incomplete class for 2D rigidbody physics. Just testing out how components can work together.
 *
 */
struct Rigidbody {
    Vec2 velocity;
};
}  // namespace Components
}  // namespace Vulpine