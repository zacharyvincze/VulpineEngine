#include "Scene.h"

#include "SceneLoader.h"
#include "Vulpine/Scene/Components/SpriteRenderer.h"
#include "Vulpine/Scene/Components/Transform.h"

namespace Vulpine {
Scene::Scene(const std::string& scene_id, const std::string& scene_file,
             Renderer& renderer)
    : m_TextureManager(renderer.GetSDLRenderer()),
      m_SceneID(scene_id),
      m_Renderer(renderer),
      m_SceneFilepath(scene_file) {}

Scene::~Scene() {}

/**
 * @brief Load all resources required by this scene
 *
 */
void Scene::Load() {
    // TODO: Load all of the resources that this scene requires.
    VP_CORE_DEBUG("Loading resources for scene {}", m_SceneID);

    if (SceneLoader::LoadScene(m_Registry, m_SceneFilepath) < 0) {
        VP_CORE_ERROR("Unable to load scene {}", m_SceneID);
        exit(EXIT_FAILURE);
    }

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