#include "Scene.h"

#include <fstream>

#include "Vulpine/Scene/Components/Components.h"
#include "Vulpine/Scene/Entity.h"
#include "Vulpine/Utils/Clock.h"
#include "Vulpine/Utils/Utils.h"

namespace Vulpine {
Scene::Scene(const std::string& scene_id, const std::string& scene_file, Renderer& renderer)
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
    VP_CORE_DEBUG("Loading resources for scene {}", m_SceneID);

    std::ifstream in_file(m_SceneFilepath);
    if (!in_file.is_open()) {
        VP_CORE_ERROR("Unable to open scene file {}", m_SceneFilepath);
        exit(EXIT_FAILURE);
    }

    nlohmann::json json;
    in_file >> json;

    // Load scene sprites into memory
    for (auto& item : json["objects"].items()) { LoadEntity(item.value()["path"].get<std::string>()); }

    m_TextureLoader.LoadTextures(m_Registry, m_TextureManager);
}

/**
 * @brief Free all resources allocated by this scene.
 *
 */
void Scene::Unload() {
    VP_CORE_DEBUG("Freeing resources from scene {}", m_SceneID);
    m_TextureManager.UnloadAll();
}

/**
 * @brief Update entities using their corresponding systems.
 *
 */
void Scene::Update() {
    m_SpriteAnimator.Update(m_Registry);
    m_Physics.Update(m_Registry);
}

/**
 * @brief Render the scene based on the current camera.
 *
 * @param renderer The SDL Renderer context to use for rendering.
 */
void Scene::RenderScene() { m_SceneRenderer.Render(m_Registry, m_Renderer, m_TextureManager); }

bool Scene::PollEvents(SceneEvents& event) {
    if (!m_SceneEvents.empty()) {
        event = m_SceneEvents.front();
        m_SceneEvents.pop();
        return true;
    }
    return false;
}

Entity Scene::CreateEntity() {
    Entity entity(m_Registry.create(), this);
    return entity;
}

Entity Scene::LoadEntity(const std::string& filepath) {
    std::ifstream in_file(filepath.c_str());
    if (!in_file.is_open()) {
        VP_CORE_ERROR("Unable to load object file {}", filepath);
        exit(EXIT_FAILURE);
    }

    nlohmann::json json;
    in_file >> json;
    in_file.close();

    Entity entity = CreateEntity();
    entity.ToObject(json);

    return entity;

    VP_CORE_DEBUG("Loaded object {}", json["name"].get<std::string>());
}

}  // namespace Vulpine
