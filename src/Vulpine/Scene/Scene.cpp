#include "Scene.h"

#include "Vulpine/Scene/Components/SpriteRenderer.h"
#include "Vulpine/Scene/Components/Transform.h"

namespace Vulpine {
Scene::Scene(const std::string& scene_id, SDL_Renderer* renderer)
    : m_TextureManager(renderer), m_SceneID(scene_id), m_Renderer(renderer) {
    const auto entity = m_Registry.create();
    m_Registry.emplace<SpriteRenderer>(entity, "data/sprites/NpcGuest.png",
                                       SDL_Rect{0, 0, 320, 184});
    m_Registry.emplace<Transform>(entity, SDL_Rect{0, 0, 320, 184});
}

Scene::~Scene() {}

/**
 * @brief Load all resources required by this scene
 *
 */
void Scene::Load() {
    // TODO: Load all of the resources that this scene requires.
    VP_CORE_DEBUG("Loading resources for scene {}", m_SceneID);

    m_TextureLoader.LoadTextures(m_Registry, m_TextureManager);
}

/**
 * @brief Free all resources allocated by this scene.
 *
 */
void Scene::Unload() {
    // TODO: Free all of the resources that this scene has used.
    VP_CORE_DEBUG("Freeing resources from scene {}", m_SceneID);
    m_TextureManager.UnloadAll();
}

/**
 * @brief Render the scene based on the current camera.
 *
 * @param renderer The SDL Renderer context to use for rendering.
 */
void Scene::RenderScene() {
    m_SceneRenderer.Render(m_Registry, m_Renderer, m_TextureManager);
}

}  // namespace Vulpine