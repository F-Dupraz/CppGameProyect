#pragma once

#ifndef __PlayState__
#define __PlayState__

#include <vector>

#include "GameState.h"
#include "GameObject.h"
#include "SDLGameObject.h"

class PlayState : public GameState
{
public:

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);

	virtual std::string getStateID() const { return s_playID; }

private:

	static const std::string s_playID;

	std::vector<GameObject*> m_gameObjects;
};

#endif // __PlayState__