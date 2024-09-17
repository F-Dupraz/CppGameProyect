#include <string>
#include <iostream>

#include "StateParser.h"
#include "PauseState.h"
#include "MenuButton.h"
#include "InputHandler.h"
#include "GameStateMachine.h"
#include "Game.h"

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
		m_gameObjects[i]->update();
}

void PauseState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
		m_gameObjects[i]->draw();
}

bool PauseState::onEnter()
{
	StateParser stateParser;

	stateParser.parseState("Datadrivenjson.json", s_pauseID, &m_gameObjects, &m_textureIDList);

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_pauseToMain);
	m_callbacks.push_back(s_resumePlay);

	setCallbacks(m_callbacks);

	std::cout << "entering PauseState\n";
	return true;
}

bool PauseState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
		m_gameObjects[i]->clean();

	m_gameObjects.clear();

	for (int i = 0; i < m_textureIDList.size(); i++)
		TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);

	std::cout << "exiting PauseState" << std::endl;
	return true;
}

void PauseState::s_pauseToMain()
{
	std::cout << "Callback pause to main\n";
	TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
}

void PauseState::s_resumePlay()
{
	TheGame::Instance()->getStateMachine()->popState();
}

void PauseState::setCallbacks(const std::vector<Callback>& callbacks)
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