#include "../Engine/Collision.hpp"
#include "../Engine/Timer.hpp"
#include "../Engine/Map.hpp"
#include "../Engine/UI.hpp"
#include "Logic.hpp"
#include "maps.hpp"

Map *map;
std::vector<ColliderComponent *> Game::colliders;

auto &wall(Game::manager.addEntity());
auto &player(Game::manager.addEntity());

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

    Map::LoadMap("assets/maps/map001.map", 25, 20);

    player.addComponent<TransformComponent>();
    player.addComponent<InputComponent>();
    player.addComponent<SpriteComponent>("player.png");
    player.addComponent<ColliderComponent>("player");

    wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
    wall.addComponent<SpriteComponent>("dirty.png");
    wall.addComponent<ColliderComponent>("wall");
}

void Logic::update()
{
    Game::manager.refresh();
    Game::manager.update();

    for (auto cc : Game::colliders)
    {
        if (Collision::check(player.getComponent<ColliderComponent>(), *cc))
        {
            // player.getComponent<TransformComponent>().velocity * -1;
            // std::cout << "Wall hit: " << Timer::elapsed() << std::endl;
        }
    }
}

void Logic::render()
{
    player.draw();
    wall.draw();
    timer();
}
