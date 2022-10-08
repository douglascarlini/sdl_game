#pragma once

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include <iostream>

class Game
{

public:
	Game();
	~Game();

	void init(const char *title, int width, int height, bool fullscreen);

	void handleEvents();
	double elapsed();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();

private:
	SDL_Renderer *renderer;
	SDL_Window *window;

	bool isRunning;
	int started;
};