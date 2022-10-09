#pragma once
#include "Game.hpp"

class UI
{
public:
    static void Text(SDL_Renderer *renderer, const char *text, int size, int x, int y);
};