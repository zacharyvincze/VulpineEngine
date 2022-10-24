#include "Physics.h"

#include "Vulpine/Scene/Components/Components.h"

namespace Vulpine {
void Physics::Update(entt::registry& registry, double delta_time) {
    auto view = registry.view<Components::Rigidbody, Components::Transform>();
    for (auto entity : view) {
        Components::Transform& transform = view.get<Components::Transform>(entity);
        Components::Rigidbody& rb = view.get<Components::Rigidbody>(entity);

        transform.position.x += rb.velocity.x * delta_time;
        transform.position.y += rb.velocity.y * delta_time;

        rb.velocity.y += 300.85f * delta_time;
    }
}
}  // namespace Vulpine