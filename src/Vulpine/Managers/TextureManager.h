#pragma once

#include <SDL2/SDL.h>

#include "Vulpine/vppch.h"

namespace Vulpine
{
class TextureManager
{
  public:
    TextureManager(SDL_Renderer *renderer);
    SDL_Texture *GetTexture(const std::string &filepath);
    void Unload(const std::string &filepath);
    void Load(const std::string &filepath);
    void UnloadAll();

  private:
    std::unordered_map<std::string, SDL_Texture *> m_Textures;
    SDL_Renderer *m_Renderer;

    SDL_Texture *GenerateTexture(const std::string &filepath);
};
} // namespace Vulpine