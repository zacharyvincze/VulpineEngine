#pragma once

#include "Vulpine/vppch.h"

namespace Vulpine {
class Physics {
   public:
    void Update(entt::registry& registry, double delta_time);
};
}  // namespace Vulpine