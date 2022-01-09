#include "TextureLoader.h"

namespace Vulpine {
void TextureLoader::LoadTextures(entt::registry& registry,
                                 TextureManager& textures) {
    auto view = registry.view<SpriteRenderer>();
    for (auto entity : view) {
        SpriteRenderer& sprite = view.get<SpriteRenderer>(entity);
        textures.Load(sprite.texture_path);
    }
}
}  // namespace Vulpine