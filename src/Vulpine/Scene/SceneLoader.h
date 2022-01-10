#pragma once

#include "Vulpine/vppch.h"

namespace Vulpine {
class SceneLoader {
   public:
    static int LoadScene(entt::registry& registry, const std::string& filepath);
};
}  // namespace Vulpine