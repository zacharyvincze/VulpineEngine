#include "Entity.h"

#include "Vulpine/Utils/Clock.h"
#include "Vulpine/Utils/Utils.h"

namespace Vulpine {
void Entity::ToObject(nlohmann::json& j) {
    for (auto& item : j["components"].items()) {
        if (item.key() == "Sprite") {
            std::vector<int> source_rect = item.value()["source_rect"].get<std::vector<int>>();
            AddComponent<Components::Sprite>(item.value()["texture_path"].get<std::string>(),
                                             Utils::ConvertVectorToRect(source_rect));
        }

        else if (item.key() == "AnimatedSprite") {
            std::vector<SDL_Rect> frames;

            for (auto& frame : item.value()["frames"].items()) {
                std::vector<int> pos = frame.value().get<std::vector<int>>();
                frames.push_back(Utils::ConvertVectorToRect(pos));
            }

            std::vector<int> animation = item.value()["animation"].get<std::vector<int>>();

            AddComponent<Components::AnimatedSprite>(
                frames, animation, 0, item.value()["frame_times"].get<std::vector<unsigned int>>(), 0.0f);
        }

        else if (item.key() == "Transform") {
            std::vector<float> position = item.value()["position"].get<std::vector<float>>();
            std::vector<float> size = item.value()["size"].get<std::vector<float>>();
            AddComponent<Components::Transform>(Utils::ConvertVectorToVec2(position), Utils::ConvertVectorToVec2(size));
        }
    }
}
}  // namespace Vulpine