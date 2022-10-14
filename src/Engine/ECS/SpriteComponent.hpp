#pragma once

#include "../TextureManager.hpp"
#include "TransformComponent.hpp"
#include "../../config.hpp"
#include "Components.hpp"
#include "Animation.hpp"
#include "SDL.h"

#include <map>

class SpriteComponent : public Component
{
private:
    bool animated = false;
    int animIndex = 0;
    int speed = 100;
    int frames = 0;

public:
    SDL_Rect src, dst;
    SDL_Texture *texture;
    TransformComponent *transform;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    std::map<const char *, Animation> animations;

    SpriteComponent() = default;
    SpriteComponent(const char *tID)
    {
        setTexture(tID);
    }

    ~SpriteComponent()
    {
        SDL_DestroyTexture(texture);
    }

    void setTexture(const char *tID)
    {
        texture = Game::assets->GetTexture(tID);
    }

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();

        src.h = transform->height;
        src.w = transform->width;
        src.x = src.y = 0;
    }

    void update() override
    {
        if (animated)
        {
            src.x = src.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
        }

        src.y = animIndex * transform->height;

        dst.x = static_cast<int>(transform->position.x) - Game::camera.x;
        dst.y = static_cast<int>(transform->position.y) - Game::camera.y;
        dst.h = transform->height * transform->scale;
        dst.w = transform->width * transform->scale;
    }

    void draw() override
    {
        TextureManager::Draw(texture, src, dst, transform->position.r, flip);
    }

    void AddAnim(const char *name, Animation anim)
    {
        animations.emplace(name, anim);
    }

    void Play(const char *animName)
    {
        animIndex = animations[animName].index;
        frames = animations[animName].frames;
        speed = animations[animName].speed;
        animated = true;
    }

    void Stop()
    {
        frames = 0;
        speed = 100;
        animIndex = 0;
        animated = false;
    }
};