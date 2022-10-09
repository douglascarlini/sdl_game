#pragma once

#include "../TextureManager.hpp"
#include "PositionComponent.hpp"
#include "../../config.hpp"
#include "Components.hpp"
#include "SDL.h"

class SpriteComponent : public Component
{
private:
    PositionComponent *position;
    SDL_Rect srcRect, destRect;
    SDL_Texture *texture;

public:
    SpriteComponent() = default;
    SpriteComponent(const char *path)
    {
        texture = TextureManager::LoadTexture(path);
    }

    void init() override
    {
        position = &entity->getComponent<PositionComponent>();

        destRect.w = destRect.h = TILE_SIZE;
        srcRect.w = srcRect.h = TILE_SIZE;
        srcRect.x = srcRect.y = 0;
    }

    void update() override
    {
        destRect.x = position->x();
        destRect.y = position->y();
    }

    void draw() override
    {
        TextureManager::Draw(texture, srcRect, destRect);
    }
};