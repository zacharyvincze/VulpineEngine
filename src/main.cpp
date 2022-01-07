#include <stdio.h>

#include "Vulpine/Core/Engine.h"
#include "Vulpine/Core/Logger.h"

int main(int argc, char** argv) {
    Vulpine::Logger::init();

    Vulpine::Engine* engine = new Vulpine::Engine();
    delete engine;
    return 0;
}