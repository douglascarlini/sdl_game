#pragma once

#include "SDL.h"
#include "ECS.hpp"
#include "SpriteComponent.hpp"
#include "TransformComponent.hpp"

class TileComponent : public Component
{
public:
    TransformComponent *transform;
    SpriteComponent *sprite;

    SDL_Rect tileRect;
    int tileID;
    char *path;

    TileComponent() = default;

    TileComponent(int x, int y, int w, int h, int id)
    {
        tileRect.x = x;
        tileRect.y = y;
        tileRect.w = w;
        tileRect.h = h;
        tileID = id;

        switch (tileID)
        {
        case 0:
            path = const_cast<char *>("water.png");
            break;

        case 1:
            path = const_cast<char *>("dirty.png");
            break;

        case 2:
            path = const_cast<char *>("grass.png");
            break;

        default:
            break;
        }
    }

    void init() override
    {
        entity->addComponent<TransformComponent>(tileRect.x, tileRect.y, tileRect.w, tileRect.h, 1);
        transform = &entity->getComponent<TransformComponent>();

        entity->addComponent<SpriteComponent>(path);
        sprite = &entity->getComponent<SpriteComponent>();
    }
};