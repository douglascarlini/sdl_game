#include "TextManager.hpp"

void TextManager::Write(SDL_Renderer *renderer, const char *text, int size, int x, int y)
{
    TTF_Init();
    
    int texW = 0;
    int texH = 0;
    SDL_Color color = {255, 255, 255};
    
    TTF_Font *font = TTF_OpenFont("../assets/fonts/retro.ttf", size);
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    TTF_CloseFont(font);
    
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = {x, y, texW, texH};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}