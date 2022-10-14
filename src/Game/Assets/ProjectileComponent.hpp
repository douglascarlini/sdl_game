#pragma once

#include "../../Engine/ECS/Components.hpp"
#include "../../Engine/Vector2D.hpp"
#include "../../Engine/ECS/ECS.hpp"

#include "../Util.hpp"

class ProjectileComponent : public Component
{
public:
    ProjectileComponent(int rng, int spd, Vector2D vel) : range(rng), speed(spd), velocity(vel) {}

    ~ProjectileComponent() {}

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        transform->velocity = velocity;
    }

    void update() override
    {
        distance += speed;

        if (distance > range)
        {
            Util::echo("out of range");
            entity->destroy();
        }

        else if (
            transform->position.x > Game::camera.x + Game::camera.w ||
            transform->position.y > Game::camera.y + Game::camera.h ||
            transform->position.x < Game::camera.x ||
            transform->position.y < Game::camera.y)
        {
            Util::echo("out of bounds");
            entity->destroy();
        }
    }

private:
    TransformComponent *transform;

    Vector2D velocity;
    int distance = 0;
    int range = 0;
    int speed = 0;
};