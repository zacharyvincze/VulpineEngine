#pragma once

#include <entt/entt.hpp>

#include "Vulpine/vppch.h"

namespace Vulpine {
class SpriteAnimator {
   public:
    void Update(entt::registry& registry);

   private:
    double m_elapsedTime = 0.0f;
};
}  // namespace Vulpine