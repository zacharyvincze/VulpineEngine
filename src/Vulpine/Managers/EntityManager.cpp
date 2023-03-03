#include "EntityManager.h"

#include <fstream>

#include "Vulpine/Scene/Entity.h"
#include "Vulpine/Scene/Scene.h"
#include "Vulpine/Utils/Utils.h"

using namespace Vulpine::Components;

namespace Vulpine
{
EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
    Clear();
}

Entity *EntityManager::CreateEntity(Scene *scene)
{
    Entity *entity = new Entity(m_internalRegistry.create(), scene);
    m_entities.push_back(entity);
    return entity;
}

Entity *EntityManager::LoadEntity(const std::string &filepath, Scene *scene)
{
    std::ifstream in_file(filepath.c_str());

    if (!in_file.is_open())
    {
        VP_CORE_ERROR("Unable to load object file {}", filepath);
        return nullptr;
    }

    nlohmann::json json;
    in_file >> json;
    in_file.close();

    Entity *entity = CreateEntity(scene);
    if (DeserializeEntity(entity, json) < 0)
    {
        VP_CORE_ERROR("Failed to parse entity: {}", filepath);
    }

    if (m_entityCache.find(filepath) == m_entityCache.end())
    {
        // Cache this entity into the entity cache for faster loading later
    }

    VP_CORE_DEBUG("Loaded entity {}", entity->name);

    return entity;
}

int EntityManager::DeserializeEntity(Entity *entity, const nlohmann::json &j)
{
    entity->name = j.value<std::string>("name", "GameObject");

    for (auto &item : j["components"].items())
    {
        if (item.key() == "Sprite")
        {
            std::vector<int> source_rect = item.value()["source_rect"].get<std::vector<int>>();
            entity->AddComponent<Sprite>((Component){}, item.value()["texture_path"].get<std::string>(),
                                         Utils::ConvertVectorToRect(source_rect));
        }

        else if (item.key() == "AnimatedSprite")
        {
            std::vector<SDL_Rect> frames;

            for (auto &frame : item.value()["frames"].items())
            {
                std::vector<int> pos = frame.value().get<std::vector<int>>();
                frames.push_back(Utils::ConvertVectorToRect(pos));
            }

            std::vector<int> animation = item.value()["animation"].get<std::vector<int>>();

            entity->AddComponent<AnimatedSprite>((Component){}, frames, animation, 0,
                                                 item.value()["frame_times"].get<std::vector<unsigned int>>(), 0.0f);
        }

        else if (item.key() == "Transform")
        {
            std::vector<float> position = item.value()["position"].get<std::vector<float>>();
            std::vector<float> size = item.value()["size"].get<std::vector<float>>();
            entity->AddComponent<Transform>((Component){}, Utils::ConvertVectorToVec2(position),
                                            Utils::ConvertVectorToVec2(size));
        }

        else if (item.key() == "Rigidbody")
        {
            std::vector<float> velocity = item.value()["velocity"].get<std::vector<float>>();
            entity->AddComponent<Rigidbody>((Component){}, Utils::ConvertVectorToVec2(velocity));
        }
    }

    return 0;
}

void EntityManager::Clear()
{
    for (Entity *entity : m_entities)
    {
        delete entity;
    }

    m_entities.clear();
    m_entityCache.clear();
    m_internalRegistry.clear();
}

} // namespace Vulpine