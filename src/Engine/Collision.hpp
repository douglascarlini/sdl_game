#pragma once
#include <SDL.h>

class Collision
{
public:
    static bool check(const SDL_Rect &recA, const SDL_Rect &recB);
};