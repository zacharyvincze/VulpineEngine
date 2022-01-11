#pragma once

#include "Vulpine/vppch.h"

namespace Vulpine {
class SceneLoader {
   public:
    static int LoadScene(entt::registry& registry, const std::string& filepath);
};

class SpriteLoader {
   public:
    static int LoadSprite(const entt::entity entity,
                          const std::string& filepath,
                          entt::registry& registry);
};
}  // namespace Vulpine