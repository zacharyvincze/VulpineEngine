#pragma once

#include <stdarg.h>

#include <entt/entt.hpp>
#include <nlohmann/json.hpp>

#include "Vulpine/Scene/Scene.h"
#include "Vulpine/Utils/Serializable.h"
#include "Vulpine/vppch.h"

namespace Vulpine
{

/**
 * @brief Wrapper for Entt Entity object. Provides more object-like abstraction to handling
 * entities.
 */
class Entity
{
  public:
    Entity(entt::entity handle, Scene *scene) : m_Entity(handle), m_Scene(scene)
    {
    }

    /**
     * @brief Adds a component to this entity.
     *
     * @tparam T The component type to add.
     * @tparam Args Any additional components to add.
     * @param args The component's initialization parameters.
     */
    template <typename T, typename... Args> void AddComponent(Args &&...args)
    {
        m_Scene->m_entityManager.GetInternalRegistry().emplace<T>(m_Entity, std::forward<Args>(args)...);
        m_Scene->OnComponentAdded<T>(*this, GetComponent<T>());
    }

    /**
     * @brief Adds a component to an entity, or replaces the component if
     * it already exists on this entity.
     *
     * @tparam T The component type to add.
     * @tparam Args Any addition components to add.
     * @param args The component's initialization parameters.
     */
    template <typename T, typename... Args> void AddOrReplaceComponent(Args &&...args)
    {
        m_Scene->m_entityManager.GetInternalRegistry().emplace_or_replace<T>(m_Entity, std::forward<Args>(args)...);
        m_Scene->OnComponentAdded<T>(*this, GetComponent<T>());
    }

    /**
     * @brief Get the Component object
     *
     * @tparam T The component to get.
     * @return T& A reference to the component.
     */
    template <typename T> T &GetComponent()
    {
        return m_Scene->m_entityManager.GetInternalRegistry().get<T>(m_Entity);
    }

    std::string name;

  private:
    entt::entity m_Entity;
    Scene *m_Scene = nullptr;
};

} // namespace Vulpine