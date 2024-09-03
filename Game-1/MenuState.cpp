#include <iostream>

#include "MenuState.h"
#include "MenuButton.h"
#include "TextureManager.h"
#include "Game.h"

const std::string MenuState::s_menuID = "MENU";

void MenuState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
		m_gameObjects[i]->update();
}

void MenuState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
		m_gameObjects[i]->draw();
}

bool MenuState::onEnter()
{
	if (TheTextureManager::Instance() == nullptr) {
		std::cerr << "Error: TheTextureManager instance is nullptr " << TheTextureManager::Instance() << ".\n";
		return false;
	}

	if (TheGame::Instance() == nullptr) {
		std::cerr << "Error: TheGane instance is nullptr.\n";
		return false;
	}

	if (!TheTextureManager::Instance()->load("./Images/play-button.png", "playbutton", TheGame::Instance()->getRenderer()))
		return false;
	
	if (!TheTextureManager::Instance()->load("./Images/exit-button.png", "exitbutton", TheGame::Instance()->getRenderer()))
		return false;


	GameObject* button1 = new MenuButton(new LoaderParams((720 / 2) - 170, (720 - (720 / 3)), 120, 66, "playbutton"));
	GameObject* button2 = new MenuButton(new LoaderParams((720 / 2) + 50, (720 - (720 / 3)), 120, 66, "exitbutton"));
	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);
	std::cout << "entering MenuState\n";
	return true;
}

bool MenuState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
		m_gameObjects[i]->clean();

	m_gameObjects.clear();
	TheTextureManager::Instance()->clearFromTextureMap("playbutton");
	TheTextureManager::Instance()->clearFromTextureMap("exitbutton");
	std::cout << "exiting MenuState\n";
	return true;
}
