#include "Physics.h"

#include "Vulpine/Scene/Components/Components.h"

namespace Vulpine {
void Physics::Update(entt::registry& registry) {
    auto view = registry.view<Components::Rigidbody, Components::Transform>();
    for (auto entity : view) {
        Components::Transform& transform = view.get<Components::Transform>(entity);
        Components::Rigidbody& rb = view.get<Components::Rigidbody>(entity);

        transform.position.x += rb.velocity.x;
        transform.position.y += rb.velocity.y;

        rb.velocity.y += 0.01f;
    }
}
}  // namespace Vulpine