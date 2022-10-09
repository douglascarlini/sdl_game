#include "TextureManager.hpp"
#include "../config.hpp"

SDL_Texture *TextureManager::LoadTexture(const char *texture)
{
    std::string textureFolder = "../assets/textures/";
    std::string imagePath = textureFolder + texture;
    const char *path = imagePath.c_str();

    // Util::echo(imagePath);

    SDL_Surface *tmpSurface = IMG_Load(path);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    return tex;
}

void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dst, SDL_RendererFlip flip)
{
    double angle = 0;
    SDL_Point center = {dst.x - dst.w / 2, dst.y - dst.h / 2};
    SDL_RenderCopyEx(Game::renderer, tex, &src, &dst, angle, &center, flip);
}