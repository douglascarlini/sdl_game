#pragma once

#include "ECS.hpp"
#include "Components.hpp"

class UIComponent : public Component
{
public:
    UIComponent(int x, int y, std::string txt, std::string fnt, SDL_Color clr) : text(txt), font(fnt), color(clr)
    {
        position.x = x;
        position.y = y;

        SetText(text);
    }

    void SetText(std::string text)
    {
        SDL_Surface *surface = TTF_RenderText_Blended(Game::assets->GetFont(font), text.c_str(), color);
        texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
        SDL_FreeSurface(surface);

        SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
    }

    void draw() override
    {
        SDL_RenderCopy(Game::renderer, texture, NULL, &position);
    }

    ~UIComponent() {}

private:
    SDL_Texture *texture;
    SDL_Rect position;
    std::string text;
    std::string font;
    SDL_Color color;
};