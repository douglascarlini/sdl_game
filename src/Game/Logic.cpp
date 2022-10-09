#include "../Engine/TextManager.hpp"
#include "../Engine/Map.hpp"
#include "Logic.hpp"
#include "maps.hpp"

Map *map;
Manager manager;
auto &player(manager.addEntity());

void Logic::init()
{
    map = new Map();
    map->LoadMap(LVL2);
    player.addComponent<TransformComponent>();
    player.addComponent<SpriteComponent>("player.png");
}

void Logic::update(double sec)
{
    manager.refresh();
    manager.update();

    player.getComponent<TransformComponent>().position.Add(Vector2D(1, 0));

    if (sec > 3)
    {
        if (lvl() != 1)
        {
            lvl(1);
            map->LoadMap(LVL1);
        }
    }
}

void Logic::render()
{
    map->DrawMap();
    player.draw();

    char timer[100];
    double t = seconds;
    sprintf(timer, "TIME: %.1fs", t);
    TextManager::Write(Game::renderer, timer, 20, 10, 10);
}
