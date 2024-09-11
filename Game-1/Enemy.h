#pragma once

#ifndef __Enemy__
#define __Enemy__

#include <string>

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class Enemy : public SDLGameObject
{
public:

	Enemy();

	void draw();
	void update();
	void clean() {};
	virtual void load(const LoaderParams* pParams0);

	int isVisibleX();

	bool isAddingX = true;
};

class EnemyCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Enemy();
	}
};

#endif // __Enemy__