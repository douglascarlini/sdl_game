#pragma once

#include "Components.hpp"
#include "../Game.hpp"
#include "ECS.hpp"
#include "SDL.h"

class InputComponent : public Component
{
public:
    TransformComponent *transform;

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
    }

    void update() override
    {
        const Uint8 *keyState = SDL_GetKeyboardState(NULL);
        switch (Game::event.type)
        {
        case SDL_KEYUP:
        case SDL_KEYDOWN:
            if (keyState[SDL_SCANCODE_W])
                transform->velocity.y -= transform->accel;
            if (keyState[SDL_SCANCODE_A])
                transform->velocity.x -= transform->accel;
            if (keyState[SDL_SCANCODE_S])
                transform->velocity.y += transform->accel;
            if (keyState[SDL_SCANCODE_D])
                transform->velocity.x += transform->accel;
            break;
        }
    }
};
