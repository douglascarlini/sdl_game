#pragma once

#include "Components.hpp"
#include "../Game.hpp"
#include "ECS.hpp"

class KeyboardController : public Component
{
public:
    TransformComponent *transform;

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
    }

    void update() override
    {
        if (Game::event.type == SDL_KEYUP) handle(Game::event.key.keysym.sym, false);
        if (Game::event.type == SDL_KEYDOWN) handle(Game::event.key.keysym.sym, true);
    }

private:
    void handle(int ev, bool down)
    {
        switch (ev)
        {
        case SDLK_w:
            if (down) transform->velocity.y = -1;
            else transform->velocity.y = 0;
            break;

        case SDLK_a:
            if (down) transform->velocity.x = -1;
            else transform->velocity.x = 0;
            break;

        case SDLK_s:
            if (down) transform->velocity.y = 1;
            else transform->velocity.y = 0;
            break;

        case SDLK_d:
            if (down) transform->velocity.x = 1;
            else transform->velocity.x = 0;
            break;
        }
    }
};