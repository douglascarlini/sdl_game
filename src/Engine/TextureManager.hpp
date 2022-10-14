#pragma once

#include "Game.hpp"

class TextureManager
{
public:
    static SDL_Texture *LoadTexture(const char *path);
    static void Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dst, SDL_RendererFlip flip);
    static void Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dst, double angle, SDL_RendererFlip flip);
};