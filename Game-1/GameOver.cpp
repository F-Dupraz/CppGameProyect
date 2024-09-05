#include "GameOver.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "MenuButton.h"
#include "Game.h"
#include "MenuState.h"
#include "PlayState.h"

const std::string GameOverState::s_gameoverID = "GAMEOVER";

void GameOverState::s_gameOverToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(new MenuState());
}
void GameOverState::s_restartPlay()
{
	TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}

void GameOverState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
		m_gameObjects[i]->update();
}

void GameOverState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
		m_gameObjects[i]->draw();
}

bool GameOverState::onEnter()
{
	if (!TheTextureManager::Instance()->load("./Images/menu-button.png", "menubutton", TheGame::Instance()->getRenderer()))
		return false;

	if (!TheTextureManager::Instance()->load("./Images/play-button.png", "playbutton", TheGame::Instance()->getRenderer()))
		return false;

	GameObject* button1 = new MenuButton(new LoaderParams((720 / 2) - 170, (720 / 3), 120, 66, "menubutton"), s_gameOverToMain);
	GameObject* button2 = new MenuButton(new LoaderParams((720 / 2) + 50, (720 / 3), 120, 66, "playbutton"), s_restartPlay);

	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);

	std::cout << "entering GameOverState\n";
	return true;
}

bool GameOverState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
		m_gameObjects[i]->clean();

	m_gameObjects.clear();

	TheTextureManager::Instance()->clearFromTextureMap("menubutton");
	TheTextureManager::Instance()->clearFromTextureMap("playbutton");

	std::cout << "exiting GameOverState\n";
	return true;
}
