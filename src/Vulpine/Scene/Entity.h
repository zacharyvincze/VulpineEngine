#pragma once

#include <stdarg.h>

#include <entt/entt.hpp>
#include <nlohmann/json.hpp>

#include "Vulpine/Scene/Scene.h"
#include "Vulpine/Utils/Serializable.h"
#include "Vulpine/vppch.h"

namespace Vulpine {

/**
 * @brief Encapsulation of entt's entity class. Just to be able to keep track of
 * certain attributes.
 *
 */
class Entity : public Serializable {
   public:
    Entity(entt::entity handle, Scene* scene) : m_Scene(scene), m_Entity(handle) {}

    template <typename T, typename... Args>
    void AddComponent(Args&&... args) {
        m_Scene->m_Registry.emplace<T>(m_Entity, std::forward<Args>(args)...);
    }

    template <typename T>
    T& GetComponent() {
        return m_Scene->m_Registry.get<T>(m_Entity);
    }

    void ToObject(nlohmann::json& j) override;

   private:
    entt::entity m_Entity;
    Scene* m_Scene = nullptr;
};

}  // namespace Vulpine