#include "../Engine/ECS/Animation.hpp"
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

    Map::LoadMap("map001", 25, 20, 1);

    player.addComponent<TransformComponent>();
    player.addComponent<SpriteComponent>("player_idle.png");
    player.getComponent<SpriteComponent>().AddAnim("Idle", Animation(0, 4, 100, true));
    player.getComponent<SpriteComponent>().Play("Idle");
    player.addComponent<ColliderComponent>("player");
    player.addComponent<InputComponent>();
    player.addGroup(groupPlayers);
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
