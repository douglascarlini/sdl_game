#include "../Engine/UI.hpp"
#include "../Engine/Timer.hpp"
#include "../Engine/Map.hpp"
#include "Logic.hpp"
#include "maps.hpp"

Map *map;
Manager manager;
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
}

void Logic::update()
{
    manager.refresh();
    manager.update();
}

void Logic::render()
{
    map->DrawMap();
    player.draw();
    timer();
}
