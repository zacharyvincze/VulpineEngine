#include "Vulpine/Core/Engine.h"
#include "Vulpine/Scene/Components/Components.h"
#include "Vulpine/Scene/Entity.h"

using namespace Vulpine;
using namespace Vulpine::Components;

int main(int argc, char **argv)
{
    srand(time(0));
    Vulpine::Engine *engine = new Vulpine::Engine();

    // Setup scenes
    Vulpine::Scene *default_scene = engine->GetSceneManager()->CreateScene("default", "data/scenes/default.scene.json");
    engine->GetSceneManager()->SetScene("default");

    // for (int i = 0; i < 100; i++)
    // {
    //     Vulpine::Entity *entity = default_scene->GetEntityManager().LoadEntity("data/objects/chaco-fall.obj.json");
    //     // entity.GetComponent<Vulpine::Components::Transform>().position = (Vulpine::Vec2){16.0f * i, 128.0f + (16 *
    //     // i)};
    //     entity->GetComponent<Rigidbody>().velocity =
    //         (Vec2){RandomFloat(-1000.0f, 1000.0f), RandomFloat(-2000.0f, -250.0f)};
    // }

    // Start the engine
    engine->Start();

    delete engine;
    return 0;
}