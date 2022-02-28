#include "Loaders.h"

#include "Vulpine/Scene/Components.h"
#include "Vulpine/Utils/Clock.h"
#include "Vulpine/Utils/Utils.h"

namespace Vulpine {
int SceneLoader::LoadScene(entt::registry& registry,
                           const std::string& filepath) {
    std::ifstream in_file(filepath);
    if (!in_file.is_open()) {
        VP_CORE_ERROR("Unable to open scene file {}", filepath);
        return -1;
    }

    nlohmann::json json;
    in_file >> json;

    // Load scene sprites into memory
    for (auto& item : json["objects"].items()) {
        const entt::entity entity = registry.create();
        if (EntityLoader::LoadEntity(entity,
                                     item.value()["path"].get<std::string>(),
                                     registry) < 0) {
            return -1;
        }
    }

    return 0;
}

/**
 * @brief Loads a sprite and inserts it into a Scene's registry.
 *
 * @param filepath the path to the sprite information file.
 * @param registry the registry to load this sprite into.
 * @return 0 on success, -1 on failure.
 */
int EntityLoader::LoadEntity(const entt::entity entity,
                             const std::string& filepath,
                             entt::registry& registry) {
    std::ifstream in_file(filepath.c_str());
    if (!in_file.is_open()) {
        VP_CORE_ERROR("Unable to load sprite file {}", filepath);
        return -1;
    }

    nlohmann::json json;
    in_file >> json;
    in_file.close();

    for (auto& item : json["components"].items()) {
        if (item.key() == "Sprite") {
            std::vector<int> source_rect =
                item.value()["source_rect"].get<std::vector<int>>();
            registry.emplace<Sprite>(
                entity, item.value()["texture_path"].get<std::string>(),
                Utils::ConvertVectorToRect(source_rect));
        }

        else if (item.key() == "AnimatedSprite") {
            std::vector<SDL_Rect> frames;

            for (auto& frame : item.value()["frames"].items()) {
                std::vector<int> pos = frame.value().get<std::vector<int>>();
                frames.push_back(Utils::ConvertVectorToRect(pos));
            }

            std::vector<int> animation =
                item.value()["animation"].get<std::vector<int>>();

            registry.emplace<AnimatedSprite>(
                entity, frames, animation, 0,
                item.value()["frame_times"].get<std::vector<unsigned int>>(),
                Clock::GetElapsed<std::chrono::milliseconds>());
        }

        else if (item.key() == "Transform") {
            std::vector<int> position =
                item.value()["position"].get<std::vector<int>>();
            registry.emplace<Transform>(entity,
                                        Utils::ConvertVectorToRect(position));
        }
    }

    VP_CORE_DEBUG("Loaded sprite {}", json["name"].get<std::string>());
    return 0;
}

}  // namespace Vulpine