#include "Scene.h"

#include <fstream>

#include "Vulpine/Scene/Components/Components.h"
#include "Vulpine/Scene/Entity.h"
#include "Vulpine/Utils/Clock.h"
#include "Vulpine/Utils/Utils.h"

namespace Vulpine
{
Scene::Scene(const std::string &scene_id, const std::string &scene_file, Renderer &renderer)
    : m_TextureManager(renderer.GetSDLRenderer()), m_SceneID(scene_id), m_Renderer(renderer),
      m_SceneFilepath(scene_file)
{
}

Scene::~Scene()
{
}

/**
 * @brief Load all resources required by this scene
 *
 */
void Scene::Load()
{
    VP_CORE_DEBUG("Loading resources for scene {}", m_SceneID);

    std::ifstream in_file(m_SceneFilepath);
    if (!in_file.is_open())
    {
        VP_CORE_ERROR("Unable to open scene file {}", m_SceneFilepath);
        exit(EXIT_FAILURE);
    }

    nlohmann::json json;
    in_file >> json;

    // Load scene sprites into memory
    for (auto &item : json["objects"].items())
    {
        m_entityManager.LoadEntity(item.value()["path"].get<std::string>(), this);
    }
}

/**
 * @brief Free all resources allocated by this scene.
 *
 */
void Scene::Unload()
{
    VP_CORE_DEBUG("Freeing resources from scene {}", m_SceneID);
    m_TextureManager.UnloadAll();
    m_entityManager.Clear();
}

/**
 * @brief Update entities using their corresponding systems.
 *
 */
void Scene::Update()
{
    m_SpriteAnimator.Update(m_entityManager.GetInternalRegistry());
    m_Physics.Update(m_entityManager.GetInternalRegistry());
}

/**
 * @brief Render the scene based on the current camera.
 *
 * @param renderer The SDL Renderer context to use for rendering.
 */
void Scene::RenderScene()
{
    m_SceneRenderer.Render(m_entityManager.GetInternalRegistry(), m_Renderer, m_cameraEntity);
}

bool Scene::PollEvents(SceneEvent &event)
{
    if (!m_SceneEvents.empty())
    {
        event = m_SceneEvents.front();
        m_SceneEvents.pop();
        return true;
    }
    return false;
}

Entity *Scene::LoadEntity(const std::string &path)
{
    return m_entityManager.LoadEntity(path, this);
}

Entity *Scene::CreateEntity()
{
    return m_entityManager.CreateEntity(this);
}

template <> void Scene::OnComponentAdded(Entity &entity, Components::Sprite &component)
{
    // Load and assign required texture pointer.
    m_TextureManager.Load(component.texture_path);
    component.texture = m_TextureManager.GetTexture(component.texture_path);
}

template <> void Scene::OnComponentAdded(Entity &entity, Components::Camera &component)
{
    VP_CORE_DEBUG("Setting main camera to: " + entity.name);
    m_cameraEntity = &entity;
}

} // namespace Vulpine
