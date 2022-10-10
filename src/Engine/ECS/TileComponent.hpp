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
    Vector2D position;

    TileComponent() = default;
    ~TileComponent()
    {
        SDL_DestroyTexture(texture);
    }

    TileComponent(int sx, int sy, int x, int y, const char *path, int scale)
    {
        texture = TextureManager::LoadTexture(path);

        dst.w = dst.h = TILE_SIZE * scale;
        src.w = src.h = TILE_SIZE;

        position.x = x;
        position.y = y;

        src.x = sx;
        src.y = sy;

        dst.x = x;
        dst.y = y;
    }

    void update() override
    {
        dst.x = position.x - Game::camera.x;
        dst.y = position.y - Game::camera.y;
    }

    void draw() override
    {
        TextureManager::Draw(texture, src, dst, SDL_FLIP_NONE);
    }
};