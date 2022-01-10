#ifndef ENGINE_H
#define ENGINE_H

#include "Vulpine/Scene/SceneManager.h"
#include "Vulpine/Utils/Clock.h"

namespace Vulpine {
class Engine {
   public:
    Engine();
    ~Engine();

   private:
    SceneManager *m_SceneManager;
    Clock m_Clock;
};
}  // namespace Vulpine

#endif  // ENGINE_H