#include "../Engine/Collision.hpp"
#include "../Engine/Timer.hpp"
#include "../Engine/Map.hpp"
#include "../Engine/UI.hpp"
#include "Logic.hpp"
#include "maps.hpp"

Map *map;
Manager manager;
auto &wall(manager.addEntity());
auto &player(manager.addEntity());

void timer()
{
    char timer[100];
    float t = Timer::elapsed();
    sprintf(timer, "TIME: %.1fs", t);
    UI::Text(Game::renderer, timer, 20, 10, 10);
}

void Logic::init()
{
    Timer::start();

    map = new Map();
    map->LoadMap(LVL2);

    player.addComponent<TransformComponent>();
    player.addComponent<KeyboardController>();
    player.addComponent<SpriteComponent>("player.png");
    player.addComponent<ColliderComponent>("player");

    wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
    wall.addComponent<SpriteComponent>("dirty.png");
    wall.addComponent<ColliderComponent>("wall");
}

void Logic::update()
{
    manager.refresh();
    manager.update();

    if (Collision::check(player.getComponent<ColliderComponent>().collider, wall.getComponent<ColliderComponent>().collider))
    {
        std::cout << "Wall hit: " << Timer::elapsed() << std::endl;
    }
}

void Logic::render()
{
    map->DrawMap();
    player.draw();
    wall.draw();
    timer();
}
