#pragma once

#ifndef __GameObject__
#define __GameObject__

#include <SDL.h>
#include <iostream>
#include <string>

#include "TextureManager.h"

class GameObject
{
public:
	virtual void load(int x, int y, int width, int height, std::string textureID);
	virtual void draw(SDL_Renderer* pRenderer);
	virtual void update();
	virtual void clean() {};

protected:
	std::string m_textureID;

	int m_currentFrame;
	int m_currentRow;

	int m_width;
	int m_height;
	int m_x;
	int m_y;
};

#endif //__GameObject__

