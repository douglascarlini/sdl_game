#pragma once
#include "Game.hpp"

class GameObject
{
public:
    GameObject(const char *texturesheet, double x, double y);
    ~GameObject();

    void Control();
    void Update();
    void Render();
    void Move();

private:
    double accel;
    double fricc;
    double xpos;
    double ypos;
    double velx;
    double vely;
    int timer;

    SDL_Texture *objTexture;
    SDL_Rect srcRect, destRect;
};