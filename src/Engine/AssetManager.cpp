#include "ECS/Components.hpp"
#include "AssetManager.hpp"

#include "../Game/Assets/ProjectileComponent.hpp"

AssetManager::AssetManager(Manager *man) : manager(man)
{
}

void AssetManager::AddTexture(std::string id, const char *path)
{
    textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture *AssetManager::GetTexture(std::string id)
{
    return textures[id];
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