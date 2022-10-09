#pragma once
#include "Game.hpp"

class TextManager
{
public:
    static void Write(SDL_Renderer *renderer, const char *text, int size, int x, int y);
};