#pragma once

#include "../TextureManager.hpp"
#include "TransformComponent.hpp"
#include "../../config.hpp"
#include "Components.hpp"
#include "SDL.h"

class SpriteComponent : public Component
{
private:
    TransformComponent *transform;
    SDL_Rect srcRect, destRect;
    SDL_Texture *texture;

public:
    SpriteComponent() = default;
    SpriteComponent(const char *path)
    {
        texture = TextureManager::LoadTexture(path);
    }

    void setTexture(const char *path)
    {
        texture = TextureManager::LoadTexture(path);
    }

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();

        destRect.w = destRect.h = TILE_SIZE;
        srcRect.w = srcRect.h = TILE_SIZE;
        srcRect.x = srcRect.y = 0;
    }

    void update() override
    {
        destRect.x = (int)transform->position.x;
        destRect.y = (int)transform->position.y;
    }

    void draw() override
    {
        TextureManager::Draw(texture, srcRect, destRect);
    }
};