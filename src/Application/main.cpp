#include "Vulpine/Core/Engine.h"
#include "Vulpine/Scene/Components.h"
#include "Vulpine/Scene/Entity.h"

int main(int argc, char** argv) {
    Vulpine::Engine* engine = new Vulpine::Engine();

    // Setup scenes
    Vulpine::Scene* default_scene = engine->GetSceneManager()->CreateScene("default", "data/scenes/default.scene.json");
    engine->GetSceneManager()->SetScene("default");

    Vulpine::Entity entity = default_scene->LoadEntity("data/objects/chaco.obj.json");
    entity.GetComponent<Vulpine::Transform>().position = (SDL_Rect){0, 32, 32, 32};

    // Start the engine
    engine->Start();

    delete engine;
    return 0;
}