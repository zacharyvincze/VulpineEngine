#include "SceneRenderer.h"

#include <SDL2/SDL.h>

#include "Vulpine/Scene/Components/Components.h"

namespace Vulpine
{

void SceneRenderer::Render(entt::registry &registry, Renderer &renderer)
{
    auto view = registry.view<Components::Sprite, Components::Transform>();
    for (auto entity : view)
    {
        Components::Transform &trans = view.get<Components::Transform>(entity);
        Components::Sprite &sprite = view.get<Components::Sprite>(entity);
        SDL_Rect position =
            (SDL_Rect){(int)trans.position.x, (int)trans.position.y, (int)trans.size.x, (int)trans.size.y};
        renderer.DrawTexture(sprite.texture, &sprite.source_rect, &position);
    }
}
} // namespace Vulpine