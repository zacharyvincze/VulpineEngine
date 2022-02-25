#include "Input.h"

std::unordered_map<SDL_Scancode, bool> Input::m_PressedKeys;
std::unordered_map<SDL_Scancode, bool> Input::m_ReleasedKeys;
std::unordered_map<SDL_Scancode, bool> Input::m_HeldKeys;
bool Input::m_IsQuit = false;

void Input::PollEvents() {
    m_ReleasedKeys.clear();
    m_PressedKeys.clear();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            m_PressedKeys[event.key.keysym.scancode] = true;
            m_HeldKeys[event.key.keysym.scancode] = true;
        } else if (event.type == SDL_KEYUP) {
            m_ReleasedKeys[event.key.keysym.scancode] = true;
            m_ReleasedKeys[event.key.keysym.scancode] = false;
        } else if (event.type == SDL_QUIT) {
            m_IsQuit = true;
        }
    }
}

bool Input::IsKeyPressed(SDL_Scancode key) { return m_PressedKeys[key]; }

bool Input::IsKeyReleased(SDL_Scancode key) { return m_ReleasedKeys[key]; }

bool Input::IsKeyHeld(SDL_Scancode key) { return m_HeldKeys[key]; }

bool Input::isQuit() { return m_IsQuit; }