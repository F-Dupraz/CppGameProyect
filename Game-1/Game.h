#pragma once

#ifndef __Game__
#define __Game__

#include <SDL.h>
#include <iostream>
#include <vector>

#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"

class Game
{
public:
	Game() {};
	//¬Game();

	bool init(const char* title, int xpos, int ypos, int width, int height, int flags);

	void render();
	void update();
	void draw();
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

	std::vector<GameObject*> m_gameObjects;

	GameObject* m_go;
	Player* m_player;
	Enemy* m_enemy1;
	Enemy* m_enemy2;
	Enemy* m_enemy3;
};

#endif /* defined(__Game__) */