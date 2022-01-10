#include "SceneRenderer.h"

#include "Vulpine/Scene/Components/SpriteRenderer.h"
#include "Vulpine/Scene/Components/Transform.h"

namespace Vulpine {

/**
 * @brief Renders all renderable entities.
 *
 * @param registry entt registry containing the entities to render.
 * @param renderer The SDL renderer context to use for rendering
 * @param textures The texture manager containing any required textures
 */
void SceneRenderer::Render(entt::registry& registry, Renderer& renderer,
                           TextureManager& textures) {
    auto view = registry.view<SpriteRenderer, Transform>();
    for (auto entity : view) {
        Transform& trans = view.get<Transform>(entity);
        SpriteRenderer& sprite_renderer = view.get<SpriteRenderer>(entity);
        renderer.DrawTexture(textures.GetTexture(sprite_renderer.texture_path),
                             &sprite_renderer.source_rect, &trans.position);
    }
}
}  // namespace Vulpine