#pragma once

#ifndef __GameOverState__
#define __GameOverState__

#include <vector>

#include "MenuState.h"
#include "GameObject.h"

class GameOverState : public MenuState
{
public:

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit() ;

	virtual std::string getStateID() const { return s_gameoverID; }

	virtual void setCallbacks(const std::vector<Callback>& callbacks);

private:

	static void s_gameOverToMain();
	static void s_restartPlay();

	static const std::string s_gameoverID;

	std::vector<GameObject*> m_gameObjects;
};

#endif // _GameOverState__