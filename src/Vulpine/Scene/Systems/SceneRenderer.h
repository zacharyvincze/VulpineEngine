#pragma once

#include "Vulpine/Managers/TextureManager.h"
#include "Vulpine/vppch.h"

namespace Vulpine {

/**
 * @brief System for rendering entities. Requires the SpriteRenderer component.
 *
 */
class SceneRenderer {
   public:
    void Render(entt::registry& registry, SDL_Renderer* renderer,
                TextureManager& textures);

   private:
};
}  // namespace Vulpine