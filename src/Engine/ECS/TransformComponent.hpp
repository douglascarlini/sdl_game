#pragma once
#include "Components.hpp"
#include "../Vector2D.hpp"

class TransformComponent : public Component
{
public:
    Vector2D position;
    Vector2D velocity;

    int height = 64;
    int width = 64;
    int scale = 1;

    float accel = 1.0;
    float fric = 0.98;
    int speed = 30;

    TransformComponent()
    {
        position.Zero();
    }

    TransformComponent(int s)
    {
        position.Zero();
        scale = s;
    }

    TransformComponent(float x, float y)
    {
        position.x = x;
        position.y = y;
    }

    TransformComponent(float x, float y, int h, int w, int s)
    {
        position.x = x;
        position.y = y;
        height = h;
        width = w;
        scale = s;
    }

    void init() override
    {
        velocity.Zero();
    }

    void update() override
    {
        velocity.x *= fric;
        velocity.y *= fric;

        position.x += velocity.x;
        position.y += velocity.y;
    }
};