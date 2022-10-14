#pragma once

#include <map>
#include <string>
#include "ECS/ECS.hpp"
#include "Vector2D.hpp"
#include "TextureManager.hpp"

class AssetManager
{
public:
    AssetManager(Manager *man);

    // GAME OBJECTS

    void CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id);
    void CreatePlayer(Vector2D pos, Vector2D vel, int range, int speed, std::string id);

    void AddTexture(std::string id, const char *name);
    SDL_Texture *GetTexture(std::string id);

    void AddFont(std::string id, const char *name, int size);
    TTF_Font *GetFont(std::string id);

    void AddMap(std::string id, const char *name);
    std::string GetMap(std::string id);

    ~AssetManager();

private:
    Manager *manager;
    std::map<std::string, std::string> maps;
    std::map<std::string, TTF_Font *> fonts;
    std::map<std::string, SDL_Texture *> textures;
};