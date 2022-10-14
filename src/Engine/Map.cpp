#include <fstream>

#include "ECS/Components.hpp"
#include "../Game/Util.hpp"
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

int _rows(std::string path)
{
    std::ifstream stream;
    stream.open(path);
    std::string text;
    int total = 0;

    while (std::getline(stream, text))
    {
        if (!text.size())
            break;
        total++;
    }

    stream.close();
    return total;
}

int _cols(std::string path)
{
    std::ifstream stream;
    stream.open(path);
    std::string text;
    int total = 0;
    int s = 0;

    std::getline(stream, text);
    if (text.size() % 3 != 0)
        s = text.size() + 1;
    total = s / 3;

    stream.close();
    return total;
}

void Map::LoadMap(Group group, int zoom)
{
    std::string path = Game::assets->GetMap(name);

    int sx, sy, dx, dy;
    std::fstream file;
    int rows, cols;
    scale = zoom;
    char c;

    rows = _rows(path);
    cols = _cols(path);

    file.open(path.c_str());

    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
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

    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            file.get(c);
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
    tile.addComponent<TileComponent>(sx, sy, x, y, name, scale);
    tile.addGroup(g);
}