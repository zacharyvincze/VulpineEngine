#pragma once

#include "Vulpine/Scene/Components/Components.h"
#include "Vulpine/Scene/Entity.h"
#include "Vulpine/vppch.h"

namespace Vulpine
{
/**
 * @brief Loads and stores entities from json files. To be used within Scene objects to keep track of entt::registry
 *
 */
class EntityManager
{
  public:
    EntityManager();
    ~EntityManager();

    /**
     * @brief Loads and returns an entity from provided JSON file.
     *
     * @param filepath  Filepath pointing to the entity's JSON representation.
     * @return Entity* A pointer to the loaded entity object.
     */
    Entity *LoadEntity(const std::string &filepath);
    Entity *CreateEntity();

    /**
     * @brief Frees all resources allocated by EntityManager
     *
     */
    void Clear();

    entt::registry &GetInternalRegistry()
    {
        return m_internalRegistry;
    }

  private:
    std::unordered_map<std::string, Vulpine::Components::Component> m_entityCache;
    std::vector<Entity *> m_entities;
    entt::registry m_internalRegistry;

    int ParseEntity(Entity *entity, const nlohmann::json &j);
};
} // namespace Vulpine