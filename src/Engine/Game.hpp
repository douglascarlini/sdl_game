#pragma once

#include <map>
#include <vector>
#include <iostream>

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

#include "ECS/ECS.hpp"

class ColliderComponent;

class Game
{
public:
	Game();
	~Game();

	void init(const char *title, int width, int height, bool fullscreen);

	static void Map(const char *sImg, const char *sMap)
	{
		map.emplace("img", sImg);
		map.emplace("map", sMap);
	}

	static void AddTile(int sx, int sy, int x, int y);
	bool running() { return isRunning; }
	void handleEvents();
	void update();
	void render();
	void clean();

	static std::vector<ColliderComponent *> colliders;
	static std::map<const char *, const char *> map;
	static SDL_Renderer *renderer;
	static SDL_Event event;
	static Manager manager;

private:
	SDL_Window *window;
	bool isRunning;
};