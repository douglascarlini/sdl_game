#include "TextureManager.hpp"
#include "../config.hpp"
#include "Game.hpp"

SDL_Texture *TextureManager::LoadTexture(const char *texture)
{
    std::string textureFolder = "assets/textures/";
    std::string imagePath = textureFolder + texture;
    const char *path = imagePath.c_str();

    SDL_Surface *tmpSurface = IMG_Load(path);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    return tex;
}

void TextureManager::Draw(SDL_Texture *texture, SDL_Rect src, SDL_Rect dst, SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(Game::renderer, texture, &src, &dst, 0, NULL, flip);
}

void TextureManager::Draw(SDL_Texture *texture, SDL_Rect src, SDL_Rect dst, double angle, SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(Game::renderer, texture, &src, &dst, angle, NULL, flip);
}