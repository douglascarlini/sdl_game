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

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
    std::string img = path + ".png";
    std::string map = path + ".map";
    Game::map["map"] = map.c_str();
    Game::map["img"] = img.c_str();

    char c;
    int sx, sy;
    std::fstream file;
    file.open("assets/maps/" + map);

    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX; x++)
        {
            file.get(c);
            sy = atoi(&c) * TILE_SIZE;
            file.get(c);
            sx = atoi(&c) * TILE_SIZE;
            Game::AddTile(sx, sy, x * TILE_SIZE, y * TILE_SIZE);
            file.ignore();
        }
    }

    file.close();
}