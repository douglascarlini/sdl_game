#include "config.hpp"
#include "Game.hpp"

Game *game = nullptr;

int main(int argc, char *argv[])
{
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();
	game->init(APP_NAME, WIN_WIDTH, WIN_HEIGHT, FULLSCREEN);

	while (game->running())
	{
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();
	return 0;
}