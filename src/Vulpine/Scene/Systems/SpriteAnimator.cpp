#include "SpriteAnimator.h"

#include "Vulpine/Scene/Components.h"

namespace Vulpine {
void SpriteAnimator::Update(entt::registry& registry) {
    auto view = registry.view<Sprite, AnimatedSprite>();
    for (auto entity : view) {
        Sprite& sprite = view.get<Sprite>(entity);
        AnimatedSprite& animated_sprite = view.get<AnimatedSprite>(entity);

        // Update sprite based on animated sprite parameters.
        }
}
}  // namespace Vulpine