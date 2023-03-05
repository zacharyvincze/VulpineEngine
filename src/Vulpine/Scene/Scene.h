#pragma once

#include <queue>

#include "Vulpine/Managers/EntityManager.h"
#include "Vulpine/Renderer/Renderer.h"
#include "Vulpine/Scene/Systems/Physics.h"
#include "Vulpine/Scene/Systems/SceneRenderer.h"
#include "Vulpine/Scene/Systems/SpriteAnimator.h"
#include "Vulpine/vppch.h"

namespace Vulpine
{

/**
 * @brief Scene events can propagate requests back to the main engine if need
 * be. This ensures that certain scripted entities are allowed to send specific
 * requests to quit and such.
 *
 */
enum SceneEvent
{
    ENGINE_QUIT
};

class Entity;

/**
 * @brief Responsible for holding game objects and resources associated
 * with a certain level in a game.
 *
 */
class Scene
{
  public:
    Scene(const std::string &scene_id, const std::string &scene_file, Renderer &renderer);
    ~Scene();

    /**
     * @brief Load all resources required by this scene
     *
     */
    void Load();

    /**
     * @brief Free all resources allocated by this scene.
     *
     */
    void Unload();

    /**
     * @brief Update entities using their corresponding systems.
     *
     */
    void Update();

    /**
     * @brief Render the scene based on the current camera.
     *
     * @param renderer The SDL Renderer context to use for rendering.
     */
    void RenderScene();

    bool PollEvents(SceneEvent &event);

    /**
     * @brief Loads a serialized entity from a file into the scene.
     *
     * @param path The path to the file containing the entity.
     * @return Entity* A pointer to the created entity.
     */
    Entity *LoadEntity(const std::string &path);

    /**
     * @brief Creates an entity for the scene.
     *
     * @return Entity* A pointer to the created entity.
     */
    Entity *CreateEntity();

  private:
    template <typename T> void OnComponentAdded(Entity &entity, T &component)
    {
    }

  private:
    std::string m_SceneID;
    std::string m_SceneFilepath;

    TextureManager m_TextureManager;
    EntityManager m_entityManager;

    // Renderer context to use for this scene
    Renderer &m_Renderer;
    Entity *m_cameraEntity = nullptr;

    // Required systems for each scene
    SceneRenderer m_SceneRenderer;
    SpriteAnimator m_SpriteAnimator;
    Physics m_Physics;

    // TODO: Worth making a message bus to handle these things.
    std::queue<SceneEvent> m_SceneEvents;

    // Allow the Entity class to access private members of scenes.
    // This is required to gain access to the registry. Though we'd
    // like to keep each scene's registry private whenever possible.
    friend class Entity;
};
} // namespace Vulpine