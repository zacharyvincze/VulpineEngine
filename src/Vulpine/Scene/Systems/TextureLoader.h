#pragma once

#include "Vulpine/Managers/TextureManager.h"
#include "Vulpine/Scene/Components/Components.h"
#include "Vulpine/vppch.h"

namespace Vulpine {
class TextureLoader {
   public:
    void LoadTextures(entt::registry& registry, TextureManager& textures);
};
}  // namespace Vulpine