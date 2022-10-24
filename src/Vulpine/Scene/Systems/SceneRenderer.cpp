#include "SceneRenderer.h"

#include "Vulpine/Scene/Components/Components.h"

namespace Vulpine {

/**
 * @brief Renders all renderable entities.
 *
 * @param registry entt registry containing the entities to render.
 * @param renderer The SDL renderer context to use for rendering
 * @param textures The texture manager containing any required textures
 */
void SceneRenderer::Render(entt::registry& registry, Renderer& renderer, TextureManager& textures) {
    auto view = registry.view<Components::Sprite, Components::Transform>();
    for (auto entity : view) {
        Components::Transform& trans = view.get<Components::Transform>(entity);
        Components::Sprite& sprite_renderer = view.get<Components::Sprite>(entity);
        SDL_Rect position = (SDL_Rect){trans.position.x, trans.position.y, trans.size.x, trans.size.y};
        renderer.DrawTexture(textures.GetTexture(sprite_renderer.texture_path), &sprite_renderer.source_rect,
                             &position);
    }
}
}  // namespace Vulpine