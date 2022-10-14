#include "../Engine/ECS/Animation.hpp"
#include "../Engine/Collision.hpp"
#include "../Engine/Vector2D.hpp"
#include "../Engine/ECS/ECS.hpp"
#include "../Engine/Timer.hpp"
#include "../Engine/Map.hpp"
#include "Logic.hpp"

#include <sstream>

extern Map *map;
extern Manager manager;

auto &label(manager.addEntity());

auto &tiles(manager.getGroup(Game::groupMap));
auto &players(manager.getGroup(Game::groupPlayers));
auto &enemies(manager.getGroup(Game::groupEnemies));
auto &colliders(manager.getGroup(Game::groupColliders));
auto &projectiles(manager.getGroup(Game::groupProjectiles));

void Logic::init()
{
    Timer::start();

    if (TTF_Init() == -1)
    {
        std::cout << "Error: SDL_TTF" << std::endl;
    }

    Game::assets->AddTexture("projectile", "assets/textures/missile.png");
    Game::assets->AddTexture("hitbox", "assets/textures/hitbox.png");
    Game::assets->AddTexture("player", "assets/textures/player.png");
    Game::assets->AddTexture("map001", "assets/textures/map001.png");
    Game::assets->AddFont("label", "assets/fonts/retro.ttf", 20);
    Game::assets->AddMap("map001", "assets/maps/map001.map");

    map = new Map("map001");
    map->LoadMap(Game::groupMap, 25, 20, 2);

    Game::assets->CreatePlayer(Vector2D(100, 100), Vector2D(10, 0), 200, 2, "player");
    Game::assets->CreateProjectile(Vector2D(100, 100), Vector2D(10, 0), 200, 2, "projectile");

    label.addComponent<UIComponent>(10, 10, "TESTE", "label", Game::assets->GetColor("white"));
}

void timer(Entity *label)
{
    char str[100];
    float t = Timer::elapsed();
    sprintf(str, "TIME: %.1fs", t);
    label->getComponent<UIComponent>().SetText(str);
}

void Logic::update()
{
    timer(&label);

    auto &player = players[0];

    Game::camera.y = player->getComponent<TransformComponent>().position.y - (WIN_HEIGHT / 2);
    Game::camera.x = player->getComponent<TransformComponent>().position.x - (WIN_WIDTH / 2);

    if (Game::camera.x < 0)
        Game::camera.x = 0;
    if (Game::camera.y < 0)
        Game::camera.y = 0;
    if (Game::camera.x > Game::camera.w)
        Game::camera.x = Game::camera.w;
    if (Game::camera.y > Game::camera.h)
        Game::camera.y = Game::camera.h;

    SDL_Rect pcol = player->getComponent<ColliderComponent>().collider;
    for (auto &c : colliders)
    {
        SDL_Rect ccol = c->getComponent<ColliderComponent>().collider;
        if (Collision::check(pcol, ccol))
        {
            player->getComponent<TransformComponent>().velocity * -1;
        }
    }

    // map move by game speed
    // for (auto t : tiles)
    // {
    //     t->getComponent<TileComponent>().dst.x += Game::speed.x;
    //     t->getComponent<TileComponent>().dst.y += Game::speed.y;
    // }
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

    for (auto &p : projectiles)
        p->draw();

    label.draw();

    // timer();
}
