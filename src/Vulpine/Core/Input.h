#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

#include <unordered_map>

/**
 * @brief Static input class for handling input related events.
 * Input::PollEvents() should only be called once a frame.
 *
 */
namespace Vulpine {

class Input {
   public:
    static void PollEvents();
    static bool IsKeyPressed(SDL_Scancode key);
    static bool IsKeyReleased(SDL_Scancode key);
    static bool IsKeyHeld(SDL_Scancode key);
    static bool isQuit();

   private:
    static std::unordered_map<SDL_Scancode, bool> m_PressedKeys;
    static std::unordered_map<SDL_Scancode, bool> m_ReleasedKeys;
    static std::unordered_map<SDL_Scancode, bool> m_HeldKeys;
    static bool m_IsQuit;
};
}  // namespace Vulpine

#endif  // INPUT_H