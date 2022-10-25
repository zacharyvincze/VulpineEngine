#pragma once

#include "Component.h"
#include "Vulpine/Core/DataStructures/Vector.h"
#include "Vulpine/vppch.h"

namespace Vulpine
{
namespace Components
{

/**
 * @brief Incomplete class for 2D rigidbody physics. Just testing out how components can work together.
 *
 */
struct Rigidbody : public Component
{
    Vec2 velocity;
};
} // namespace Components
} // namespace Vulpine