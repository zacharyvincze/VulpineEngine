#include "SceneRenderer.h"

#include <SDL2/SDL.h>

#include "Vulpine/Core/Input.h"
#include "Vulpine/Scene/Components/Components.h"
#include "Vulpine/Scene/Entity.h"

namespace Vulpine
{

void SceneRenderer::Render(entt::registry &registry, Renderer &renderer, Entity *camera)
{
    if (!camera)
    {
        VP_CORE_WARN("No camera for rendering.");
        return;
    }

    // Handle camera movements (temp)
    auto cam_view = registry.view<Components::Camera, Components::Transform>();
    for (auto entity : cam_view)
    {
        Components::Transform &transform = cam_view.get<Components::Transform>(entity);
        Components::Camera &cam = cam_view.get<Components::Camera>(entity);

        if (Input::IsKeyHeld(SDL_SCANCODE_LEFT))
        {
            transform.position.x -= 2;
        }

        if (Input::IsKeyHeld(SDL_SCANCODE_RIGHT))
        {
            transform.position.x += 2;
        }

        if (Input::IsKeyHeld(SDL_SCANCODE_UP))
        {
            transform.position.y -= 2;
        }

        if (Input::IsKeyHeld(SDL_SCANCODE_DOWN))
        {
            transform.position.y += 2;
        }

        if (Input::IsKeyHeld(SDL_SCANCODE_E))
        {
            cam.zoom.x += 0.1f;
            cam.zoom.y += 0.1f;
        }

        if (Input::IsKeyHeld(SDL_SCANCODE_Q))
        {
            cam.zoom.x -= 0.1f;
            cam.zoom.y -= 0.1f;
        }
    }

    auto view = registry.view<Components::Sprite, Components::Transform>();
    for (auto entity : view)
    {
        Components::Transform &trans = view.get<Components::Transform>(entity);
        Components::Sprite &sprite = view.get<Components::Sprite>(entity);

        // Offset position by camera transform
        Components::Transform &camera_transform = camera->GetComponent<Components::Transform>();
        Components::Camera &camera_obj = camera->GetComponent<Components::Camera>();

        SDL_Rect position =
            (SDL_Rect){(int)(trans.position.x - camera_transform.position.x),
                       (int)(trans.position.y - camera_transform.position.y), (int)(trans.size.x * camera_obj.zoom.x),
                       (int)(trans.size.y * camera_obj.zoom.y)};

        renderer.DrawTexture(sprite.texture, &sprite.source_rect, &position);
    }
}
} // namespace Vulpine