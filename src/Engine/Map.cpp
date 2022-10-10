#include <fstream>

#include "ECS/Components.hpp"
#include "../config.hpp"
#include "ECS/ECS.hpp"
#include "Game.hpp"
#include "Map.hpp"

extern Manager manager;

Map::Map(const char *sName) : name(sName)
{
}

Map::~Map()
{
}

void Map::LoadMap(Group group, int rows, int cols, int zoom)
{
    int sx, sy, dx, dy;
    scale = zoom;

    char c;
    std::fstream file;
    std::string str = std::string(name) + ".map";

    file.open("assets/maps/" + str);

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

            AddTile(sx, sy, dx, dy, group);

            file.ignore();
        }
    }

    file.ignore();

    for (int y = 0; y < cols; y++)
    {
        for (int x = 0; x < rows; x++)
        {
            file.get(c);
            if (c == '1')
            {
                dy = y * TILE_SIZE * scale;
                dx = x * TILE_SIZE * scale;
                auto &tcol(manager.addEntity());
                tcol.addComponent<ColliderComponent>("hitbox", dx, dy, TILE_SIZE);
                tcol.addGroup(Game::groupColliders);
            }
            file.ignore();
        }
    }

    file.close();
}

void Map::AddTile(int sx, int sy, int x, int y, Group g)
{
    auto &tile(manager.addEntity());
    std::string img = std::string(name) + ".png";
    tile.addComponent<TileComponent>(sx, sy, x, y, img.c_str(), scale);
    tile.addGroup(g);
}