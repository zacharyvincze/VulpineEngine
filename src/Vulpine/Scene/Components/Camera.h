#pragma once

#include "Component.h"
#include "Vulpine/Core/DataStructures/Vector.h"
#include "Vulpine/vppch.h"

namespace Vulpine
{
namespace Components
{
struct Camera : public Component
{
    Vec2 zoom;
};
} // namespace Components
} // namespace Vulpine