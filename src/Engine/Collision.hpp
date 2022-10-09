#pragma once
#include <SDL.h>

class ColliderComponent;

class Collision
{
public:
    static bool check(const SDL_Rect &recA, const SDL_Rect &recB);
    static bool check(const ColliderComponent &colA, const ColliderComponent &colB);
};