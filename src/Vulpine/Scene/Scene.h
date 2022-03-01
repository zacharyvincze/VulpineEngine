#pragma once

#include <queue>

#include "Vulpine/Renderer/Renderer.h"
#include "Vulpine/Scene/Systems/SceneRenderer.h"
#include "Vulpine/Scene/Systems/SpriteAnimator.h"
#include "Vulpine/Scene/Systems/TextureLoader.h"
#include "Vulpine/vppch.h"

namespace Vulpine {

/**
 * @brief Scene events can propagate requests back to the main engine if need
 * be. This ensures that certain scripted entities are allowed to send specific
 * requests to quit and such.
 *
 */
enum SceneEvents { ENGINE_QUIT };

class Entity;

/**
 * @brief Responsible for holding game objects and resources associated
 * with a certain level in a game.
 *
 */
class Scene {
   public:
    Scene(const std::string& scene_id, const std::string& scene_file,
          Renderer& renderer);
    ~Scene();

    void Load();
    void LoadEntity(const std::string& filepath);
    void Unload();

    void Update();
    void RenderScene();

    Entity CreateEntity();

    bool PollEvents(SceneEvents& event);

   private:
    entt::registry m_Registry;
    std::string m_SceneID;
    std::string m_SceneFilepath;

    TextureManager m_TextureManager;

    // Renderer context to use for this scene
    Renderer& m_Renderer;

    // Required systems for each scene
    SceneRenderer m_SceneRenderer;
    TextureLoader m_TextureLoader;
    SpriteAnimator m_SpriteAnimator;

    std::queue<SceneEvents> m_SceneEvents;

    // Allow the Entity class to access private members of scenes.
    // This is required to gain access to the registry. Though we'd
    // like to keep each scene's registry private whenever possible.
    friend class Entity;
};
}  // namespace Vulpine