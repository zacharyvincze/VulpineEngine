#include "Vulpine/Core/Engine.h"
#include "Vulpine/Scene/Components/Components.h"
#include "Vulpine/Scene/Entity.h"

float RandomFloat(float min, float max) {
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

int main(int argc, char** argv) {
    srand(time(0));
    Vulpine::Engine* engine = new Vulpine::Engine();

    // Setup scenes
    Vulpine::Scene* default_scene = engine->GetSceneManager()->CreateScene("default", "data/scenes/default.scene.json");
    engine->GetSceneManager()->SetScene("default");

    for (int i = 0; i < 10000; i++) {
        Vulpine::Entity entity = default_scene->LoadEntity("data/objects/chaco-fall.obj.json");
        // entity.GetComponent<Vulpine::Components::Transform>().position = (Vulpine::Vec2){16.0f * i, 128.0f + (16 *
        // i)};
        entity.GetComponent<Vulpine::Components::Rigidbody>().velocity =
            (Vulpine::Vec2){RandomFloat(-1000.0f, 1000.0f), RandomFloat(-2000.0f, -250.0f)};
    }

    // Start the engine
    engine->Start();

    delete engine;
    return 0;
}