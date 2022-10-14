#pragma once

#include <vector>
#include <iostream>

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

#include "ECS/ECS.hpp"
#include "Vector2D.hpp"
#include "AssetManager.hpp"

class ColliderComponent;
class AssetManager;

class Game
{
public:
	Game();
	~Game();

	void init(const char *title, int width, int height, bool fullscreen);

	bool running() { return isRunning; }
	void handleEvents();
	void update();
	void render();
	void clean();

	static SDL_Renderer *renderer;
	static AssetManager *assets;
	static SDL_Event event;
	static SDL_Rect camera;
	static Vector2D speed;

	enum groups : std::size_t
	{
		groupMap,
		groupPlayers,
		groupEnemies,
		groupColliders,
		groupProjectiles,
	};

private:
	SDL_Window *window;
	bool isRunning;
};