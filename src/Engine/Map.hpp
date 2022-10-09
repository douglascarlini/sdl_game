#pragma once
#include <string>
#include "Game.hpp"

class Map
{
public:
    Map();
    ~Map();

    static void LoadMap(std::string math, int sizeX, int sizeY);

private:
};