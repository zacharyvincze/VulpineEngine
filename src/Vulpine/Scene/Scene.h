#pragma once

#include "Vulpine/Scene/Systems/SceneRenderer.h"
#include "Vulpine/Scene/Systems/TextureLoader.h"
#include "Vulpine/vppch.h"

namespace Vulpine {

/**
 * @brief Responsible for holding game objects and resources associated
 * with a certain level in a game.
 *
 */
class Scene {
   public:
    Scene(const std::string& scene_id, SDL_Renderer* renderer);
    ~Scene();

    void Load();
    void Unload();

    void RenderScene();

   private:
    entt::registry m_Registry;
    std::string m_SceneID;

    TextureManager m_TextureManager;

    // Renderer context to use for this scene
    SDL_Renderer* m_Renderer;

    // Required systems for each scene
    SceneRenderer m_SceneRenderer;
    TextureLoader m_TextureLoader;
};
}  // namespace Vulpine