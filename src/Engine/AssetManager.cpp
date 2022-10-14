#include "ECS/Components.hpp"
#include "AssetManager.hpp"

#include "../Game/Assets/ProjectileComponent.hpp"

AssetManager::AssetManager(Manager *man) : manager(man)
{
    AddColor("white", {255, 255, 255, 255});
    AddColor("green", {0, 255, 0, 255});
    AddColor("blue", {0, 0, 255, 255});
    AddColor("red", {255, 0, 0, 255});
    AddColor("black", {0, 0, 0, 255});
}

void AssetManager::AddTexture(std::string id, const char *path)
{
    textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture *AssetManager::GetTexture(std::string id)
{
    return textures[id];
}

void AssetManager::AddColor(std::string id, SDL_Color color)
{
    colors.emplace(id, color);
}

SDL_Color AssetManager::GetColor(std::string id)
{
    return colors[id];
}

void AssetManager::AddFont(std::string id, const char *path, int size)
{
    fonts.emplace(id, TTF_OpenFont(path, size));
}

TTF_Font *AssetManager::GetFont(std::string id)
{
    return fonts[id];
}

void AssetManager::AddMap(std::string id, const char *path)
{
    maps.emplace(id, path);
}

std::string AssetManager::GetMap(std::string id)
{
    return maps[id];
}

AssetManager::~AssetManager()
{
}

// GAME OBJECTS

void AssetManager::CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id)
{
    auto &projectile(manager->addEntity());

    projectile.addComponent<TransformComponent>(pos.x, pos.y, TILE_SIZE, TILE_SIZE, 1);
    projectile.addComponent<ProjectileComponent>(range, speed, vel);
    projectile.addComponent<ColliderComponent>("projectile");
    projectile.addComponent<SpriteComponent>(id.c_str());
    projectile.addGroup(Game::groupProjectiles);
}

void AssetManager::CreatePlayer(Vector2D pos, Vector2D vel, int range, int speed, std::string id)
{
    auto &player(manager->addEntity());

    player.addComponent<TransformComponent>(pos.x, pos.y);
    player.addComponent<SpriteComponent>("player");
    player.getComponent<TransformComponent>().velocity.r = 1;
    player.getComponent<SpriteComponent>().AddAnim("Idle", Animation(0, 4, 100, true));
    player.getComponent<SpriteComponent>().Play("Idle");
    player.addComponent<ColliderComponent>("player");
    player.addComponent<InputComponent>();
    player.addGroup(Game::groupPlayers);
}