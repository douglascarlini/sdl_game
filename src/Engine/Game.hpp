#pragma once

#include <iostream>

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

#include "ECS/ECS.hpp"

class Game
{

public:
	Game();
	~Game();

	void init(const char *title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();
	
	double elapsed() { return (SDL_GetTicks() - started) / 1000.0f; }

	static SDL_Renderer *renderer;

private:
	SDL_Window *window;
	bool isRunning;
	int started;
};