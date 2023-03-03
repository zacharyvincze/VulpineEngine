#pragma once

#include <entt/entt.hpp>

#include "System.h"
#include "Vulpine/Managers/TextureManager.h"
#include "Vulpine/Renderer/Renderer.h"
#include "Vulpine/vppch.h"

namespace Vulpine
{

/**
 * @brief System for rendering entities. Requires the SpriteRenderer component.
 *
 */
class SceneRenderer : public System
{
  public:
    void Render(entt::registry &registry, Renderer &renderer);

  private:
};
} // namespace Vulpine