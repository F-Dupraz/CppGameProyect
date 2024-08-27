#pragma once

#ifndef __MenuState__
#define __MenuState__

#include <iostream>

#include "GameState.h"

class MenuState : public GameState
{
public:
	virtual void update() = 0;
	virtual void render() = 0;

	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;

	virtual std::string getStateID() const { return s_menuID; }

private:
	static const std::string s_menuID;

}

#endif // __MenuState__