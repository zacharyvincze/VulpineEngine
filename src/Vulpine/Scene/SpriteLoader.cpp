#include "SpriteLoader.h"

#include "Vulpine/Scene/Components/SpriteRenderer.h"
#include "Vulpine/Scene/Components/Transform.h"

namespace Vulpine {

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