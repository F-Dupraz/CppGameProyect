#include "MenuState.h"

const std::string MenuState::s_menuID = "PLAY";

void MenuState::update()
{
	// nothing for now
}
void MenuState::render()
{
	// nothing for now
}
bool MenuState::onEnter()
{
	std::cout << "entering PlayState\n";
	return true;
}
bool MenuState::onExit()
{
	std::cout << "exiting PlayState\n";
	return true;
}