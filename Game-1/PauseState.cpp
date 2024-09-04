#include <string>
#include <iostream>

#include "PauseState.h"
#include "MenuButton.h"
#include "InputHandler.h"
#include "Game.h"

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::s_pauseToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(new MenuState());
}

void PauseState::s_resumePlay()
{
	TheGame::Instance()->getStateMachine()->popState();
}

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
	if (!TheTextureManager::Instance()->load("./Images/menu-button.png", "menubutton", TheGame::Instance()->getRenderer()))
		return false;

	if (!TheTextureManager::Instance()->load("./Images/play-button.png", "playbutton", TheGame::Instance()->getRenderer()))
		return false;

	GameObject* pause_button1 = new MenuButton(new LoaderParams((720 / 2) - 170, (720 / 3), 120, 66, "playbutton"), s_resumePlay);
	GameObject* pause_button2 = new MenuButton(new LoaderParams((720 / 2) + 50, (720 / 3), 120, 66, "menubutton"), s_pauseToMain);
	m_gameObjects.push_back(pause_button1);
	m_gameObjects.push_back(pause_button2);

	std::cout << "entering PauseState\n";
	return true;
}

bool PauseState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
		m_gameObjects[i]->clean();

	m_gameObjects.clear();

	TheTextureManager::Instance()->clearFromTextureMap("menubutton");
	TheTextureManager::Instance()->clearFromTextureMap("playbutton");

	TheInputHandler::Instance()->reset();

	std::cout << "exiting PauseState\n";
	return true;
}