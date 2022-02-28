#include "Scene.h"

#include "Vulpine/Scene/Components.h"
#include "Vulpine/Scene/Loaders.h"
#include "Vulpine/Utils/Clock.h"

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

    // TODO: Remove this later, this is just some animated sprite testing
    entt::entity animated = m_Registry.create();
    m_Registry.emplace<Sprite>(animated, "data/sprites/NpcGuest.png",
                               (SDL_Rect){128, 0, 16, 16});
    std::vector<SDL_Rect> animated_sprite_list = {(SDL_Rect){128, 0, 16, 16},
                                                  (SDL_Rect){144, 0, 16, 16}};

    m_Registry.emplace<AnimatedSprite>(
        animated, animated_sprite_list, 0, 2000,
        Clock::GetElapsed<std::chrono::milliseconds>());
    m_Registry.emplace<Transform>(animated, (SDL_Rect){0, 0, 16, 16});

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
 * @brief Update entities using their corresponding systems.
 *
 */
void Scene::Update() { m_SpriteAnimator.Update(m_Registry); }

/**
 * @brief Render the scene based on the current camera.
 *
 * @param renderer The SDL Renderer context to use for rendering.
 */
void Scene::RenderScene() {
    m_SceneRenderer.Render(m_Registry, m_Renderer, m_TextureManager);
}

bool Scene::PollEvents(SceneEvents& event) {
    if (!m_SceneEvents.empty()) {
        event = m_SceneEvents.front();
        m_SceneEvents.pop();
        return true;
    }
    return false;
}

}  // namespace Vulpine