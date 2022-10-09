#pragma once
#include <string>
#include "Game.hpp"

class Map
{
public:
    Map();
    ~Map();

    static void LoadMap(Group group, std::string path, int rows, int cols, int scale);

private:
};