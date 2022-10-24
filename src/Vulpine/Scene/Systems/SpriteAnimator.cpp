#include "SpriteAnimator.h"

#include "Vulpine/Scene/Components/Components.h"
#include "Vulpine/Utils/Clock.h"

namespace Vulpine {
void SpriteAnimator::Update(entt::registry& registry) {
    auto view = registry.view<Components::Sprite, Components::AnimatedSprite>();
    for (auto entity : view) {
        Components::Sprite& sprite = view.get<Components::Sprite>(entity);
        Components::AnimatedSprite& animated_sprite = view.get<Components::AnimatedSprite>(entity);

        // Update sprite based on animated sprite parameters.
        if (Clock::GetElapsed<std::chrono::milliseconds>() - animated_sprite.last_update >=
            animated_sprite.frame_times[animated_sprite.current_frame]) {
            animated_sprite.current_frame++;
            if (animated_sprite.current_frame >= animated_sprite.animation.size()) {
                animated_sprite.current_frame = 0;
            }

            animated_sprite.last_update = Clock::GetElapsed<std::chrono::milliseconds>();

            sprite.source_rect = animated_sprite.frames[animated_sprite.animation[animated_sprite.current_frame]];
        }
    }
}  // namespace Vulpine
}  // namespace Vulpine