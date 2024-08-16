#pragma once

#ifndef __Game__
#define __Game__

#include <SDL.h>
#include <iostream>

#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"

class Game
{
public:
	Game() {};
	//¬Game();

	bool init(const char* title, int xpos, int ypos, int width, int height, int flags);

	void render();
	void update();
	void handleEvents();
	void clean();

	bool running() { return m_bRunning; }

private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	SDL_Texture* m_pTexture; 
	SDL_Rect m_sourceRectangle;
	SDL_Rect m_destinationRectangle;

	int m_currentFrame;

	bool m_bRunning;

	GameObject m_go;
	Player m_player;
};

#endif /* defined(__Game__) */