#include "ECS/Components.hpp"
#include "../Game/Logic.hpp"
#include "../config.hpp"
#include "Vector2D.hpp"
#include "Game.hpp"
#include "Map.hpp"
#include "UI.hpp"

Map *map;
Logic logic;
Manager manager;
Vector2D Game::speed;
SDL_Event Game::event;
SDL_Renderer *Game::renderer = nullptr;
SDL_Rect Game::camera = {0, 0, WIN_WIDTH, WIN_HEIGHT};
AssetManager *Game::assets = new AssetManager(&manager);

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(const char *title, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)

		flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer)

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		isRunning = true;
	}

	logic.init();
}

void Game::handleEvents()
{
	const Uint8 *keyState = SDL_GetKeyboardState(NULL);
	SDL_PollEvent(&event);

	if (keyState[SDL_SCANCODE_ESCAPE])
		isRunning = false;

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	manager.refresh();
	manager.update();
	logic.update();
}

void Game::render()
{
	SDL_RenderClear(renderer);

	logic.render();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
}