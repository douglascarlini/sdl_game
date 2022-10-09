#pragma once
#include "Game.hpp"

class Map
{
public:
    Map();
    ~Map();

    void LoadMap(int arr[20][25]);
    void DrawMap();

private:
    SDL_Rect src, dst;

    SDL_Texture *grass;
    SDL_Texture *water;
    SDL_Texture *dirty;

    int map[20][25];
};