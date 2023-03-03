#pragma once

#include <entt/entt.hpp>

#include "Vulpine/Scene/Systems/System.h"
#include "Vulpine/vppch.h"

namespace Vulpine
{
class SpriteAnimator : public System
{
  public:
    void Update(entt::registry &registry);

  private:
    double m_elapsedTime = 0.0f;
};
} // namespace Vulpine