#include "Loaders.h"

#include "Vulpine/Scene/Components.h"

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
    for (auto& item : json["sprites"].items()) {
        const entt::entity entity = registry.create();
        if (SpriteLoader::LoadSprite(entity,
                                     item.value()["path"].get<std::string>(),
                                     registry) < 0) {
            return -1;
        }
        std::vector<int> dest =
            item.value()["position"].get<std::vector<int>>();
        registry.emplace<Transform>(
            entity, SDL_Rect{dest[0], dest[1], dest[2], dest[3]});
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
int SpriteLoader::LoadSprite(const entt::entity entity,
                             const std::string& filepath,
                             entt::registry& registry) {
    std::ifstream in_file(filepath.c_str());
    if (!in_file.is_open()) {
        VP_CORE_ERROR("Unable to load sprite file {}", filepath);
        return -1;
    }

    nlohmann::json in_json;
    in_file >> in_json;

    in_file.close();

    std::vector<int> source = in_json["source"].get<std::vector<int>>();

    SDL_Rect source_rect = SDL_Rect{source[0], source[1], source[2], source[3]};

    registry.emplace<SpriteRenderer>(
        entity, in_json["texture_path"].get<std::string>(), source_rect);

    VP_CORE_DEBUG("Loaded sprite {}", filepath);
    return 0;
}

}  // namespace Vulpine