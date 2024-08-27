#pragma once

#ifndef __PlayState__
#define __PlayState__

#include <iostream>

#include "GameState.h"

class PlayState : public GameState
{
public:
	virtual void update() = 0;
	virtual void render() = 0;

	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;

	virtual std::string getStateID() const { return s_playID; }

private:
	static const std::string s_playID;

}

#endif // __PlayState__