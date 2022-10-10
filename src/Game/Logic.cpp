#include "../Engine/ECS/Animation.hpp"
#include "../Engine/Collision.hpp"
#include "../Engine/Vector2D.hpp"
#include "../Engine/ECS/ECS.hpp"
#include "../Engine/Timer.hpp"
#include "../Engine/Map.hpp"
#include "../Engine/UI.hpp"
#include "Logic.hpp"

extern Map *map;
extern Manager manager;

auto &wall(manager.addEntity());
auto &player(manager.addEntity());

auto &tiles(manager.getGroup(Game::groupMap));
auto &players(manager.getGroup(Game::groupPlayers));
auto &enemies(manager.getGroup(Game::groupEnemies));
auto &colliders(manager.getGroup(Game::groupColliders));

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

    map = new Map("map001");
    map->LoadMap(Game::groupMap, 25, 20, 1);

    player.addComponent<TransformComponent>();
    player.addComponent<SpriteComponent>("player_idle.png");
    player.getComponent<SpriteComponent>().AddAnim("Idle", Animation(0, 4, 100, true));
    player.getComponent<SpriteComponent>().Play("Idle");
    player.addComponent<ColliderComponent>("player");
    player.addComponent<InputComponent>();
    player.addGroup(Game::groupPlayers);
}

void Logic::update()
{
    Game::camera.y = player.getComponent<TransformComponent>().position.y - (WIN_HEIGHT / 2);
    Game::camera.x = player.getComponent<TransformComponent>().position.x - (WIN_WIDTH / 2);

    if (Game::camera.x < 0)
        Game::camera.x = 0;
    if (Game::camera.y < 0)
        Game::camera.y = 0;
    if (Game::camera.x > Game::camera.w)
        Game::camera.x = Game::camera.w;
    if (Game::camera.y > Game::camera.h)
        Game::camera.y = Game::camera.h;

    // map move by game speed
    // for (auto t : tiles)
    // {
    //     t->getComponent<TileComponent>().dst.x += Game::speed.x;
    //     t->getComponent<TileComponent>().dst.y += Game::speed.y;
    // }

    SDL_Rect pcol = player.getComponent<ColliderComponent>().collider;
    for (auto &c : colliders)
    {
        SDL_Rect ccol = c->getComponent<ColliderComponent>().collider;
        if (Collision::check(pcol, ccol))
        {
            player.getComponent<TransformComponent>().velocity * -1;
        }
    }
}

void Logic::render()
{
    for (auto &t : tiles)
        t->draw();

    for (auto &p : players)
        p->draw();

    for (auto &e : enemies)
        e->draw();

    for (auto &c : colliders)
        c->draw();

    timer();
}
