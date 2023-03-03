#pragma once

#include <stdarg.h>

#include <entt/entt.hpp>
#include <nlohmann/json.hpp>

#include "Vulpine/Scene/Scene.h"
#include "Vulpine/Utils/Serializable.h"
#include "Vulpine/vppch.h"

namespace Vulpine
{

/// @brief Wrapper for Entt Entity object. Provides more object-like abstraction to handling
/// entities.
class Entity
{
  public:
    Entity(entt::entity handle, Scene *scene) : m_Entity(handle), m_Scene(scene)
    {
    }

    template <typename T, typename... Args> void AddComponent(Args &&...args)
    {
        m_Scene->m_entityManager.GetInternalRegistry().emplace<T>(m_Entity, std::forward<Args>(args)...);
        m_Scene->OnComponentAdded<T>(*this, GetComponent<T>());
    }

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