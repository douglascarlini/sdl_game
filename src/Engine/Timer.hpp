#pragma once
#include "SDL.h"

class Timer
{
public:
    static void start()
    {
        started = SDL_GetTicks();
    }

    static float elapsed()
    {
        return (SDL_GetTicks() - started) / 1000.0f;
    }

private:
    static int started;
};