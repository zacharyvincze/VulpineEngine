#pragma once

#include "Vulpine/vppch.h"

namespace Vulpine {
class SpriteAnimator {
   public:
    void Update(entt::registry& registry, double delta_time);

   private:
    double m_elapsedTime = 0.0f;
};
}  // namespace Vulpine