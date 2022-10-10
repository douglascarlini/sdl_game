#pragma once

#include <map>
#include <vector>
#include <iostream>

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

#include "ECS/ECS.hpp"
#include "Vector2D.hpp"

class ColliderComponent;

class Game
{
public:
	Game();
	~Game();

	void init(const char *title, int width, int height, bool fullscreen);

	static void Map(const char *sImg, const char *sMap, int zoom)
	{
		map.emplace("img", sImg);
		map.emplace("map", sMap);
		scale = zoom;
	}

	static void AddTile(int sx, int sy, int x, int y, Group g);
	bool running() { return isRunning; }
	void handleEvents();
	void update();
	void render();
	void clean();

	static std::vector<ColliderComponent *> colliders;
	static std::map<const char *, const char *> map;
	static SDL_Renderer *renderer;
	static SDL_Event event;
	static SDL_Rect camera;
	static Manager manager;
	static Vector2D speed;
	static int scale;

private:
	SDL_Window *window;
	bool isRunning;
};