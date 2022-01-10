#pragma once

#include "Vulpine/Managers/TextureManager.h"
#include "Vulpine/Renderer/Renderer.h"
#include "Vulpine/vppch.h"

namespace Vulpine {

/**
 * @brief System for rendering entities. Requires the SpriteRenderer component.
 *
 */
class SceneRenderer {
   public:
    void Render(entt::registry& registry, Renderer& renderer,
                TextureManager& textures);

   private:
};
}  // namespace Vulpine