#include "SceneLoader.h"

#include "SpriteLoader.h"
#include "Vulpine/Scene/Components/Transform.h"

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
}  // namespace Vulpine