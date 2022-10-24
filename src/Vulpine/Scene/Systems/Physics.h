#pragma once

#include <entt/entt.hpp>

#include "Vulpine/vppch.h"

namespace Vulpine {
class Physics {
   public:
    void Update(entt::registry& registry);
};
}  // namespace Vulpine