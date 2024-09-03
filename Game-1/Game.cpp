#include <iostream>
#include <vector>

#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "GameStateMachine.h"


Game* Game::s_pInstance = nullptr;

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	// attempt to initialize SDL
	int img_flags = IMG_INIT_PNG;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0 && IMG_Init(img_flags) == img_flags)
	{
		int flags = 0;

		std::cout << "SDL init success\n";

		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (m_pWindow != 0)
		{
			std::cout << "window creation success\n";
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if (m_pRenderer != 0)
			{
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
			}
			else
			{
				std::cout << "renderer init fail\n";
				return false;
			}
		}
		else
		{
			std::cout << "window init fail\n";
			return false;
		}
	}
	else
	{
		std::cerr << "Failed to initialize SDL: " << SDL_GetError() << "\n\n";
		std::cerr << "Failed to initialize SDL_image: " << IMG_GetError() << "\n\n";
		std::cout << "SDL init fail\n";
		return false;
	}

	std::cout << "init success\n";
	m_bRunning = true; 

	m_pGameStateMachine = new GameStateMachine();

	m_pGameStateMachine->changeState(new MenuState());

	return true;
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer);

	m_pGameStateMachine->render();

	SDL_RenderPresent(m_pRenderer);
}

void Game::clean()
{
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	TheInputHandler::Instance()->clean();
	SDL_Quit();
}

void Game::handleEvents()
{
	TheInputHandler::Instance()->update();

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
	{
		m_pGameStateMachine->changeState(new PlayState());
	}
}

void Game::update()
{
	m_pGameStateMachine->update();
}