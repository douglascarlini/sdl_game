#pragma once

#include "SDL.h"
#include "ECS.hpp"
#include "../../config.hpp"
#include "SpriteComponent.hpp"
#include "TransformComponent.hpp"

class TileComponent : public Component
{
public:
    SDL_Texture *texture;
    SDL_Rect src, dst;

    TileComponent() = default;
    ~TileComponent()
    {
        SDL_DestroyTexture(texture);
    }

    TileComponent(int sx, int sy, int x, int y, const char *path)
    {
        texture = TextureManager::LoadTexture(path);
        src.w = src.h = TILE_SIZE;
        src.x = sx;
        src.y = sy;

        dst.w = dst.h = TILE_SIZE;
        dst.x = x;
        dst.y = y;
    }

    void draw() override
    {
        TextureManager::Draw(texture, src, dst, SDL_FLIP_NONE);
    }
};