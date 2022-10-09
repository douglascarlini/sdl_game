#include "../Engine/Collision.hpp"
#include "../Engine/Timer.hpp"
#include "../Engine/Map.hpp"
#include "../Engine/UI.hpp"
#include "Logic.hpp"

Map *map;
std::vector<ColliderComponent *> Game::colliders;

enum groupLabels : std::size_t
{
    groupMap,
    groupPlayers,
    groupEnemies,
    groupColliders
};

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

    Map::LoadMap("map001.map", 25, 20);

    player.addComponent<TransformComponent>();
    player.addComponent<InputComponent>();
    player.addComponent<SpriteComponent>("player_idle.png", 4, 100);
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayers);

    wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
    wall.addComponent<SpriteComponent>("dirty.png");
    wall.addComponent<ColliderComponent>("wall");
    wall.addGroup(groupMap);
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

auto &tiles(Game::manager.getGroup(groupMap));
auto &players(Game::manager.getGroup(groupPlayers));
auto &enemies(Game::manager.getGroup(groupEnemies));

void Logic::render()
{
    for (auto &t : tiles)
        t->draw();
    for (auto &p : players)
        p->draw();
    for (auto &e : enemies)
        e->draw();
    timer();
}
