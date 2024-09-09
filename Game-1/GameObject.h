#pragma once

#ifndef __GameObject__
#define __GameObject__

#include <SDL.h>
#include <iostream>
#include <string>

#include "TextureManager.h"
#include "LoaderParams.h"

class GameObject
{
public:

	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;

	virtual void load(const LoaderParams* pParams) = 0;

protected:

	GameObject(const LoaderParams* pParams) {}
	virtual ~GameObject() {}

	std::string m_textureID;

	int m_currentFrame;
	int m_currentRow;

	int m_width;
	int m_height;
	int m_x;
	int m_y;
};

#endif // __GameObject__

