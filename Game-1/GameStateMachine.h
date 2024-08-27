#pragma once

#ifndef __GameStateMachine__
#define __GameStateMachine__

#include <vector>
#include <iostream>

#include "GameState.h"

class GameStateMachine
{
public:
	void update();
	void render();

	void pushState(GameState* pState);
	void changeState(GameState* pState);
	void popState();

private:
	std::vector<GameState*> m_gameStates;

}

#endif // __GameStateMachine__