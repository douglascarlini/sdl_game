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
    TransformComponent *transform;
    SDL_Rect srcRect, destRect;
    SDL_Texture *texture;

    bool animated = false;
    int speed = 100;
    int frames = 0;

public:
    int animIndex = 0;

    std::map<const char *, Animation> animations;

    SpriteComponent() = default;
    SpriteComponent(const char *path)
    {
        setTexture(path);
    }

    ~SpriteComponent()
    {
        SDL_DestroyTexture(texture);
    }

    void setTexture(const char *path)
    {
        texture = TextureManager::LoadTexture(path);
    }

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();

        srcRect.h = transform->height;
        srcRect.w = transform->width;
        srcRect.x = srcRect.y = 0;
    }

    void update() override
    {
        if (animated)

            srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);

        srcRect.y = animIndex * transform->height;

        destRect.x = static_cast<int>(transform->position.x);
        destRect.y = static_cast<int>(transform->position.y);
        destRect.h = transform->height * transform->scale;
        destRect.w = transform->width * transform->scale;
    }

    void draw() override
    {
        TextureManager::Draw(texture, srcRect, destRect);
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
};