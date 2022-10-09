#pragma once
#include <string>
#include "SDL.h"
#include "Components.hpp"

class ColliderComponent : public Component
{
public:
    TransformComponent *transform;
    SDL_Rect collider;
    std::string tag;

    ColliderComponent(std::string t)
    {
        tag = t;
    }

    void init() override
    {
        // if (!entity->hasComponent<TransformComponent>())
        //     entity->addComponent<TransformComponent>();
        transform = &entity->getComponent<TransformComponent>();
    }

    void update() override
    {
        collider.x = static_cast<int>(transform->position.x);
        collider.y = static_cast<int>(transform->position.y);
        collider.h = transform->height * transform->scale;
        collider.w = transform->width * transform->scale;
    }
};