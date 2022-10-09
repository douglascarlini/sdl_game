#include "TextureManager.hpp"
#include "../config.hpp"
#include "Map.hpp"

Map::Map()
{
    grass = TextureManager::LoadTexture("grass.png");
    water = TextureManager::LoadTexture("water.png");
    dirty = TextureManager::LoadTexture("dirty.png");

    dst.x = dst.y = 0;

    src.x = src.y = 0;
    src.w = src.h = TILE_SIZE;
    dst.w = dst.h = TILE_SIZE;
}

void Map::LoadMap(int arr[20][25])
{
    for (int row = 0; row < 20; row++)
    {
        for (int col = 0; col < 20; col++)
        {
            map[row][col] = arr[row][col];
        }
    }
}

void Map::DrawMap()
{
    int type = 0;
    for (int row = 0; row < 20; row++)
    {
        for (int col = 0; col < 20; col++)
        {
            type = map[row][col];

            dst.x = col * TILE_SIZE;
            dst.y = row * TILE_SIZE;

            switch (type)
            {
            case 0:
                TextureManager::Draw(water, src, dst);
                break;

            case 1:
                TextureManager::Draw(grass, src, dst);
                break;

            case 2:
                TextureManager::Draw(dirty, src, dst);
                break;

            default:
                break;
            }
        }
    }
}