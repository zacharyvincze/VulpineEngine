#include "SceneRenderer.h"

#include "Vulpine/Scene/Components.h"

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
    auto view = registry.view<Sprite, Transform>();
    for (auto entity : view) {
        Transform& trans = view.get<Transform>(entity);
        Sprite& sprite_renderer = view.get<Sprite>(entity);
        renderer.DrawTexture(textures.GetTexture(sprite_renderer.texture_path),
                             &sprite_renderer.source_rect, &trans.position);
    }
}
}  // namespace Vulpine