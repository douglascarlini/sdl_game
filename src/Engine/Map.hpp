#pragma once

#include <map>
#include <string>
#include "Game.hpp"

class Map
{
public:
    Map(const char *sName);
    ~Map();

    int scale;
    void AddTile(int sx, int sy, int x, int y, Group g);
    void LoadMap(Group group, int rows, int cols, int scale);

private:
    const char *name;
};