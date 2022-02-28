#include "Vulpine/Core/Engine.h"

int main(int argc, char** argv) {
    Vulpine::Engine* engine = new Vulpine::Engine();

    // Setup scenes
    engine->GetSceneManager()->CreateScene("default",
                                           "data/scenes/default.scene.json");
    engine->GetSceneManager()->SetScene("default");

    // Start the engine
    engine->Start();

    delete engine;
    return 0;
}