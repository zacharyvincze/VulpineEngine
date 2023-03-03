#include "TextureManager.h"

#include <SDL2/SDL_image.h>

#include "Vulpine/Core/Logger.h"

namespace Vulpine
{
TextureManager::TextureManager(SDL_Renderer *renderer)
{
    m_Renderer = renderer;
}

SDL_Texture *TextureManager::GetTexture(const std::string &filepath)
{
    return m_Textures.at(filepath);
}

void TextureManager::Load(const std::string &filepath)
{
    // Check if this texture has been loaded already
    if (m_Textures.count(filepath))
    {
        // Duplicate loading of textures should not cause a warning. This is normal behavior
        // that is handled by the TextureManager.
        // VP_CORE_WARN("Duplicate loading of texture {}", filepath);
        return;
    }

    // Load this texture onto the GPU and insert it into our map
    m_Textures.insert(std::pair<std::string, SDL_Texture *>(filepath, GenerateTexture(filepath)));

    VP_CORE_DEBUG("Loaded texture {}", filepath);
}

void TextureManager::Unload(const std::string &filepath)
{
    // Remove a single texture from the manager
    if (m_Textures.count(filepath) != 1)
    {
        VP_CORE_WARN("Unable to unload texture {}", filepath);
        return;
    }

    VP_CORE_DEBUG("Freed texture {}", filepath);
    SDL_Texture *texture = m_Textures.at(filepath);
    SDL_DestroyTexture(texture);
    m_Textures.erase(filepath);
}

void TextureManager::UnloadAll()
{
    // Free all textures currently loaded
    for (std::pair<std::string, SDL_Texture *> texture : m_Textures)
    {
        VP_CORE_DEBUG("Freed texture {}", texture.first);
        SDL_DestroyTexture(texture.second);
    }

    m_Textures.clear();
}

SDL_Texture *TextureManager::GenerateTexture(const std::string &filepath)
{
    SDL_Surface *surface = IMG_Load(filepath.c_str());
    if (surface == NULL)
    {
        VP_CORE_ERROR("Unable to load texture from file {}", filepath);
        exit(EXIT_FAILURE);
        return NULL;
    }

    SDL_SetColorKey(surface, SDL_TRUE, 0x000000);

    SDL_Texture *texture = SDL_CreateTextureFromSurface(m_Renderer, surface);
    if (texture == NULL)
    {
        VP_CORE_ERROR("Unable to create texture from surface {}", filepath);
        exit(EXIT_FAILURE);
        return NULL;
    }

    SDL_FreeSurface(surface);

    return texture;
}
} // namespace Vulpine