#include <string>
#include <iostream>

#include "PlayState.h"
#include "Game.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
		m_gameObjects[i]->update();
}

void PlayState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
		m_gameObjects[i]->draw();
}

bool PlayState::onEnter()
{
	if (!TheTextureManager::Instance()->load("./Images/pixil-frame-0.png", "PlayerT", TheGame::Instance()->getRenderer()))
		return false;

	GameObject* player = new Player(new LoaderParams((720 / 2), 100, 85, 100, "PlayerT"));

	m_gameObjects.push_back(player);

	std::cout << "entering PlayState\n";
	return true;
}

bool PlayState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
		m_gameObjects[i]->clean();

	m_gameObjects.clear();

	TheTextureManager::Instance()->clearFromTextureMap("PlayerT");

	std::cout << "exiting PlayState\n";
	return true;
}