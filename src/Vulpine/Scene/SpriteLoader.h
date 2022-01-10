#pragma once

#include "Vulpine/vppch.h"

namespace Vulpine {
class SpriteLoader {
   public:
    static int LoadSprite(const entt::entity entity,
                          const std::string& filepath,
                          entt::registry& registry);
};
}  // namespace Vulpine