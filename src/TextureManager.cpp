#include "TextureManager.hpp"

SDL_Texture *TextureManager::LoadTexture(const char *texture)
{
    std::string textureFolder = "../assets/textures/";
    std::string imagePath = textureFolder + texture;
    const char *path = imagePath.c_str();

    SDL_Surface *tmpSurface = IMG_Load(path);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    return tex;
}

void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dst)
{
    SDL_RenderCopy(Game::renderer, tex, &src, &dst);
}