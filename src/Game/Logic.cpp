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
auto &projectiles(manager.getGroup(Game::groupProjectiles));

void timer()
{
    char timer[100];
    float t = Timer::elapsed();
    sprintf(timer, "TIME: %.1fs", t);
    UI::Text(Game::renderer, timer, 10, 10, 20);
}

void Logic::init()
{
    Timer::start();

    Game::assets->AddTexture("projectile", "assets/textures/hitbox.png");
    Game::assets->AddTexture("hitbox", "assets/textures/hitbox.png");
    Game::assets->AddTexture("player", "assets/textures/player.png");
    Game::assets->AddTexture("map001", "assets/textures/map001.png");
    Game::assets->AddMap("map001", "assets/maps/map001.map");

    map = new Map("map001");
    map->LoadMap(Game::groupMap, 25, 20, 2);

    player.addComponent<TransformComponent>();
    player.addComponent<SpriteComponent>("player");
    player.getComponent<SpriteComponent>().AddAnim("Idle", Animation(0, 4, 100, true));
    player.getComponent<SpriteComponent>().Play("Idle");
    player.addComponent<ColliderComponent>("player");
    player.addComponent<InputComponent>();
    player.addGroup(Game::groupPlayers);

    player.getComponent<TransformComponent>().velocity.r = 1;

    Game::assets->CreateProjectile(Vector2D(100, 100), Vector2D(10, 0), 200, 2, "projectile");
}

void Logic::update()
{
    player.getComponent<TransformComponent>().position.r += player.getComponent<TransformComponent>().velocity.r;

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

    for (auto &p : projectiles)
        p->draw();

    timer();

    float vx = player.getComponent<TransformComponent>().velocity.x;
    float vy = player.getComponent<TransformComponent>().velocity.y;

    char s[100];
    sprintf(s, "VEL: %.1f x %.1f", vx, vy);
    UI::Text(Game::renderer, s, 10, 40, 20);
}
