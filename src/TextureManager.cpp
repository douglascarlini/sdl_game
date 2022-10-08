#include "TextureManager.hpp"

SDL_Texture *TextureManager::LoadTexture(const char *texture, SDL_Renderer *ren)
{
    std::string textureFolder = "../assets/textures/";
    std::string imagePath = textureFolder + texture;
    const char *path = imagePath.c_str();

    SDL_Surface *tmpSurface = IMG_Load(path);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    return tex;
}