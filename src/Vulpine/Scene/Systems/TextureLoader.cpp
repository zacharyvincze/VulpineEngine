#include "TextureLoader.h"

namespace Vulpine
{
void TextureLoader::LoadTextures(entt::registry &registry, TextureManager &textures)
{
    auto view = registry.view<Components::Sprite>();
    std::set<std::string> unique_textures;
    for (auto entity : view)
    {
        Components::Sprite &sprite = view.get<Components::Sprite>(entity);
        unique_textures.insert(sprite.texture_path);
    }

    // Prevent duplicate loading of textures by
    // iterating through the set of collected textures.
    for (std::string unique_texture : unique_textures)
    {
        textures.Load(unique_texture);
    }
}
} // namespace Vulpine