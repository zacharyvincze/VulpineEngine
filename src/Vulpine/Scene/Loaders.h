#pragma once

#include "Vulpine/vppch.h"

namespace Vulpine {
class SceneLoader {
   public:
    static int LoadScene(entt::registry& registry, const std::string& filepath);
};

class EntityLoader {
   public:
    static int LoadEntity(const entt::entity entity,
                          const std::string& filepath,
                          entt::registry& registry);
};
}  // namespace Vulpine