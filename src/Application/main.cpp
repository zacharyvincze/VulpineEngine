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

    // Start the engine
    engine->Start();

    delete engine;
    return 0;
}