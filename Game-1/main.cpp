#include "Game.h"

const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 720;

Game* g_game = 0;

int main(int argc, char* args[])
{
	g_game = new Game();

	g_game->init("New Game!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	while (g_game->running())
	{
		g_game->handleEvents();
		g_game->update();
		g_game->render();

		SDL_Delay(10);
	}

	g_game->clean();

	return 0;
}
