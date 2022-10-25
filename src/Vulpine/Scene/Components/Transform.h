#pragma once

#include "Component.h"
#include "Vulpine/Utils/Serializable.h"
#include "Vulpine/vppch.h"

namespace Vulpine
{
namespace Components
{
/**
 * @brief Positioning component for 2D objects.
 *
 */
struct Transform : public Component
{
    Vec2 position;
    Vec2 size;
};
} // namespace Components
} // namespace Vulpine