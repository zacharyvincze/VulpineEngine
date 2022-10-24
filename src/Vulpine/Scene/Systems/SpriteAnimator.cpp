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
        animated_sprite.elapsed_time += Clock::GetDeltaTime<std::chrono::milliseconds::period>();
        while (animated_sprite.elapsed_time >= animated_sprite.frame_times[animated_sprite.current_frame]) {
            // Update sprite's frame if enough time has passed. Remember to deduct the elapsed time of the
            // animated sprite on a frame change.
            animated_sprite.elapsed_time -= animated_sprite.frame_times[animated_sprite.current_frame];
            animated_sprite.current_frame++;

            // Reset frame back to 0th frame if we've reached the end of the sequence
            if (animated_sprite.current_frame >= animated_sprite.animation.size()) {
                animated_sprite.current_frame = 0;
            }

            sprite.source_rect = animated_sprite.frames[animated_sprite.animation[animated_sprite.current_frame]];
        }
    }
}  // namespace Vulpine
}  // namespace Vulpine