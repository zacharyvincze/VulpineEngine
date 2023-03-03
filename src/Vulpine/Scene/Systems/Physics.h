#pragma once

#include <entt/entt.hpp>

#include "System.h"
#include "Vulpine/vppch.h"

namespace Vulpine
{
class Physics : public System
{
  public:
    void Update(entt::registry &registry);
};
} // namespace Vulpine