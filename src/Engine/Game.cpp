#include "ECS/Components.hpp"
#include "../Game/Logic.hpp"
#include "../config.hpp"
#include "Vector2D.hpp"
#include "Game.hpp"
#include "Map.hpp"
#include "UI.hpp"

Map *map;
Logic logic;
int Game::scale;
Vector2D Game::speed;
Manager Game::manager;
SDL_Event Game::event;
SDL_Renderer *Game::renderer = nullptr;
std::map<const char *, const char *> Game::map;
std::vector<ColliderComponent *> Game::colliders;
SDL_Rect Game::camera = {0, 0, WIN_WIDTH, WIN_HEIGHT};

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

void Game::AddTile(int sx, int sy, int x, int y, Group g)
{
	auto &tile(manager.addEntity());
	tile.addComponent<TileComponent>(sx, sy, x, y, map["img"], scale);
	tile.addGroup(g);
}