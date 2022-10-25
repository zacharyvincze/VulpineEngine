#pragma once

#include <stdarg.h>

#include <entt/entt.hpp>
#include <nlohmann/json.hpp>

#include "Vulpine/Utils/Serializable.h"
#include "Vulpine/vppch.h"

namespace Vulpine
{

/**
 * @brief Encapsulation of entt's entity class. Just to be able to keep track of
 * certain attributes.
 *
 */
class Entity
{
  public:
    Entity(entt::entity handle, entt::registry &registry) : m_Entity(handle), m_registry(registry)
    {
    }
    std::string name;

    template <typename T, typename... Args> void AddComponent(Args &&...args)
    {
        m_registry.emplace<T>(m_Entity, std::forward<Args>(args)...);
    }

    template <typename T> T &GetComponent()
    {
        return m_registry.get<T>(m_Entity);
    }

  private:
    entt::entity m_Entity;
    entt::registry &m_registry;
};

} // namespace Vulpine