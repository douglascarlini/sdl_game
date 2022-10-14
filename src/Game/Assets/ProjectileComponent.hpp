#pragma once

#include "../../Engine/ECS/Components.hpp"
#include "../../Engine/Vector2D.hpp"
#include "../../Engine/ECS/ECS.hpp"

#include "../Util.hpp"

class ProjectileComponent : public Component
{
public:
    ProjectileComponent(Vector2D vel, int rng) : velocity(vel), range(rng) {}

    ~ProjectileComponent() {}

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        transform->velocity = velocity;
        initial = *transform;
    }

    void update() override
    {
        distance = Util::distance(transform->position, initial.position);

        if (distance > range)
        {
            Util::echo("out of range");
            // entity->destroy();
        }

        else if (Util::out_bounds(transform->position))
        {
            Util::echo("out of bounds");
            // entity->destroy();
        }
    }

private:
    TransformComponent *transform;
    TransformComponent initial;

    Vector2D velocity;
    int distance = 0;
    int range = 0;
};