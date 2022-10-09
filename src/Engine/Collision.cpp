#include "Collision.hpp"
#include "ECS/ColliderComponent.hpp"

bool Collision::check(const SDL_Rect &recA, const SDL_Rect &recB)
{
    return (
        recA.x + recA.w > recB.x &&
        recB.x + recB.w > recA.x &&
        recA.y + recA.h > recB.y &&
        recB.y + recB.h > recA.y);
}

bool Collision::check(const ColliderComponent &colA, const ColliderComponent &colB)
{
    if (check(colA.collider, colB.collider))
    {
        // std::cout << colA.tag << " hit: " << colB.tag << std::endl;
        return true;
    }
    else
    {
        return false;
    }
}