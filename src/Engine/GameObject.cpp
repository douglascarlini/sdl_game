#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(const char *texturesheet, double x, double y)
{
    timer = 0;

    xpos = x;
    ypos = y;
    velx = 0;
    vely = 0;
    accel = 0.5;
    fricc = 0.98;

    objTexture = TextureManager::LoadTexture(texturesheet);
}

void GameObject::Move()
{
    velx *= fricc;
    vely *= fricc;

    Control();

    xpos += velx;
    ypos += vely;
}

void GameObject::Control()
{
    int a = 50;
    int b = a + 20;
    int c = b + 30;

    if (timer < a)
    {
        velx += accel;
    }
    else if (timer < b)
    {
        vely += accel;
    }
    else if (timer < c)
    {
        velx -= accel;
    }
}

void GameObject::Update()
{
    timer += 1;

    srcRect.h = 64;
    srcRect.w = 64;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;

    Move();
}

void GameObject::Render()
{
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}