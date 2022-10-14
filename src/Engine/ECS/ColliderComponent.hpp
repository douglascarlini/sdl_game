#pragma once
#include <string>
#include "SDL.h"
#include "Components.hpp"

class ColliderComponent : public Component
{
public:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect collider;
    SDL_Rect src, dst;
    std::string tag;

    ColliderComponent(std::string t)
    {
        tag = t;
    }

    ColliderComponent(std::string t, int x, int y, int s)
    {
        tag = t;
        collider.x = x;
        collider.y = y;
        collider.w = collider.h = s;
    }

    void init() override
    {
        // if (!entity->hasComponent<TransformComponent>())
        //     entity->addComponent<TransformComponent>();
        transform = &entity->getComponent<TransformComponent>();

        src = {0, 0, TILE_SIZE, TILE_SIZE};
        texture = Game::assets->GetTexture("hitbox");
        dst = {collider.x, collider.y, collider.w, collider.h};
    }

    void update() override
    {
        if (tag != "hitbox")
        {
            collider.x = static_cast<int>(transform->position.x);
            collider.y = static_cast<int>(transform->position.y);
            collider.h = transform->height * transform->scale;
            collider.w = transform->width * transform->scale;
        }

        dst.x = collider.x - Game::camera.x;
        dst.y = collider.y - Game::camera.y;
    }

    void draw() override
    {
        TextureManager::Draw(texture, src, dst, SDL_FLIP_NONE);
    }
};