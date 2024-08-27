#pragma once

#ifndef __Game__
#define __Game__

#include <SDL.h>
#include <iostream>
#include <vector>

#include "TextureManager.h"
#include "InputHandler.h"
#include "GameObject.h"
#include "SDLGameObject.h"
#include "Player.h"
#include "Enemy.h"

class Game
{
public:

	static Game* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new Game();
			return s_pInstance;
		}
		return s_pInstance;
	}

	bool init(const char* title, int xpos, int ypos, int width, int height, int flags);

	void render();
	void update();
	void draw();
	void handleEvents();
	void clean();
	void quit() { m_bRunning = false; }

	bool running() { return m_bRunning; }
	SDL_Renderer* getRenderer() const { return m_pRenderer; }

private:

	Game() {};
	static Game* s_pInstance;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	SDL_Texture* m_pTexture; 
	SDL_Rect m_sourceRectangle;
	SDL_Rect m_destinationRectangle;

	int m_currentFrame;

	bool m_bRunning;

	std::vector<GameObject*> m_gameObjects;

};

typedef Game TheGame;

#endif // __Game__