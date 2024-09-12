#pragma once

#ifndef __MainMenuState__
#define __MainMenuState__

#include "MenuState.h"
#include "MenuButton.h"
#include "GameObject.h"

class MainMenuState : public MenuState
{
public:

	virtual void update() {}
	virtual void render() {}

	virtual bool onEnter();
	virtual bool onExit() { return true; }

	virtual std::string getStateID() const { return s_menuID; }

private:

	virtual void setCallbacks(const std::vector<Callback>& callbacks);

	static void s_menuToPlay() {}
	static void s_exitFromMenu() {}

	static const std::string s_menuID;

	std::vector<GameObject*> m_gameObjects;
};

#endif // __MainMenuState__