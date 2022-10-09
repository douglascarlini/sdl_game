#include "Map.hpp"
#include "Game.hpp"
#include "TextManager.hpp"
#include "ECS/Components.hpp"

Map *map;
Manager manager;
auto &player(manager.addEntity());

SDL_Renderer *Game::renderer = nullptr;

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

		started = SDL_GetTicks();
		isRunning = true;
	}

	map = new Map();

	player.addComponent<PositionComponent>();
	player.addComponent<SpriteComponent>("player.png");
}

double Game::elapsed()
{
	return (SDL_GetTicks() - started) / 1000.0f;
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

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
}

void Game::render()
{
	SDL_RenderClear(renderer);

	map->DrawMap();
	player.draw();

	char timer[100];
	double t = elapsed();
	sprintf(timer, "TIME: %.1fs", t);
	TextManager::Write(renderer, timer, 20, 10, 10);

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
}