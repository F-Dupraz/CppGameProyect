#include <string>
#include <iostream>

#include "MainMenuState.h"
#include "MenuButton.h"
#include "TextureManager.h"
#include "Game.h"
#include "StateParser.h"

const std::string MainMenuState::s_menuID = "MENU";

void MainMenuState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void MainMenuState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool MainMenuState::onEnter()
{
	StateParser stateParser;

	stateParser.parseState("Datadrivenjson.json", s_menuID, &m_gameObjects, &m_textureIDList);

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_menuToPlay);
	m_callbacks.push_back(s_exitFromMenu);

	setCallbacks(m_callbacks);

	std::cout << "Entering MenuState\n";

	return true;
}

bool MainMenuState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
		m_gameObjects[i]->clean();

	m_gameObjects.clear();

	for (int i = 0; i < m_textureIDList.size(); i++)
		TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);

	std::cout << "exiting MainMenuState" << std::endl;
	return true;
}

void MainMenuState::s_menuToPlay()
{
	TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}

void MainMenuState::s_exitFromMenu()
{
	TheGame::Instance()->quit();
}

void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks)
{
	for (int i = 0; i < m_gameObjects.size(); ++i)
	{
		if (dynamic_cast<MenuButton*>(m_gameObjects[i]))
		{
			MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
			pButton->setCallback(callbacks[pButton->getCallbackID()]);
		}
	}
}