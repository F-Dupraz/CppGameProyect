#include "GameOver.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "MenuButton.h"
#include "Game.h"
#include "MenuState.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "StateParser.h"

const std::string GameOverState::s_gameoverID = "GAMEOVER";

void GameOverState::s_gameOverToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
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
	StateParser stateParser;

	stateParser.parseState("Datadrivenjson.json", s_gameoverID, &m_gameObjects, &m_textureIDList);

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_gameOverToMain);
	m_callbacks.push_back(s_restartPlay);

	setCallbacks(m_callbacks);

	std::cout << "entering GameOverState\n";
	return true;
}

bool GameOverState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
		m_gameObjects[i]->clean();

	m_gameObjects.clear();

	for (int i = 0; i < m_textureIDList.size(); i++)
		TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);

	std::cout << "exiting PauseState" << std::endl;
	return true;
}

void GameOverState::setCallbacks(const std::vector<Callback>& callbacks)
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
