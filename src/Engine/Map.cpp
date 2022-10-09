#include <fstream>

#include "../config.hpp"
#include "Game.hpp"
#include "Map.hpp"

Map::Map()
{
}

Map::~Map()
{
}

void Map::LoadMap(std::string path, int rows, int cols, int scale)
{
    int sx, sy, dx, dy;
    std::string img = path + ".png";
    std::string map = path + ".map";
    Game::Map(img.c_str(), map.c_str(), scale);

    char c;
    std::fstream file;
    file.open("assets/maps/" + map);

    for (int y = 0; y < cols; y++)
    {
        for (int x = 0; x < rows; x++)
        {
            file.get(c);
            sy = atoi(&c) * TILE_SIZE;
            dy = y * TILE_SIZE * scale;

            file.get(c);
            sx = atoi(&c) * TILE_SIZE;
            dx = x * TILE_SIZE * scale;

            Game::AddTile(sx, sy, dx, dy);
            file.ignore();
        }
    }

    file.close();
}