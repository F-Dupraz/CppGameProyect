#include "Game.h"

const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 720;

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char* args[])
{
	Uint32 frameStart, frameTime;

	if (TheGame::Instance()->init("Chapter 1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false))
	{
		while (TheGame::Instance()->running())
		{
			frameStart = SDL_GetTicks();

			TheGame::Instance()->handleEvents();
			TheGame::Instance()->update();
			TheGame::Instance()->render();

			frameTime = SDL_GetTicks() - frameStart;
			if (frameTime < DELAY_TIME)
				SDL_Delay((int)(DELAY_TIME - frameTime));
		}
	}
	else
		std::cout << "Game init failure - " << SDL_GetError() << std::endl;

	TheGame::Instance()->clean();
	return 0;
}