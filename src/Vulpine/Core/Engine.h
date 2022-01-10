#ifndef ENGINE_H
#define ENGINE_H

#include "Vulpine/Scene/SceneManager.h"

namespace Vulpine {
class Engine {
   public:
    Engine();
    ~Engine();

   private:
    SceneManager *m_SceneManager;
};
}  // namespace Vulpine

#endif  // ENGINE_H