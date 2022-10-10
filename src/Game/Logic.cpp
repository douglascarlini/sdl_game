#include "../Engine/ECS/Animation.hpp"
#include "../Engine/Collision.hpp"
#include "../Engine/Vector2D.hpp"
#include "../Engine/Timer.hpp"
#include "../Engine/Map.hpp"
#include "../Engine/UI.hpp"
#include "Logic.hpp"

enum groupLabels : std::size_t
{
    groupMap,
    groupPlayers,
    groupEnemies,
    groupColliders
};

auto &wall(Game::manager.addEntity());
auto &player(Game::manager.addEntity());

auto &tiles_0(Game::manager.getGroup(groupMap));
auto &players(Game::manager.getGroup(groupPlayers));
auto &enemies(Game::manager.getGroup(groupEnemies));

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

    Map::LoadMap(groupMap, "map001", 25, 20, 1);

    player.addComponent<TransformComponent>();
    player.addComponent<SpriteComponent>("player_idle.png");
    player.getComponent<SpriteComponent>().AddAnim("Idle", Animation(0, 4, 100, true));
    player.getComponent<SpriteComponent>().Play("Idle");
    player.addComponent<ColliderComponent>("player");
    player.addComponent<InputComponent>();
    player.addGroup(groupPlayers);

    Game::speed.x = -1;
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

    // for (auto t : tiles_0)
    // {
    //     t->getComponent<TileComponent>().dst.x += Game::speed.x;
    //     t->getComponent<TileComponent>().dst.y += Game::speed.y;
    // }

    // for (auto cc : Game::colliders)
    // {
    //     if (Collision::check(player.getComponent<ColliderComponent>(), *cc))
    //     {
    //         // player.getComponent<TransformComponent>().velocity * -1;
    //         // std::cout << "Wall hit: " << Timer::elapsed() << std::endl;
    //     }
    // }
}

void Logic::render()
{
    for (auto &t : tiles_0)
        t->draw();

    for (auto &p : players)
        p->draw();

    for (auto &e : enemies)
        e->draw();

    timer();
}
