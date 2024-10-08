#include <string>
#include <iostream>

#include "PlayState.h"
#include "PauseState.h"
#include "GameOver.h"
#include "StateParser.h"
#include "InputHandler.h"
#include "Game.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
		TheGame::Instance()->getStateMachine()->pushState(new PauseState());

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		if (i > 0)
		{
			if (checkCollision(dynamic_cast<SDLGameObject*> (m_gameObjects[0]), dynamic_cast<SDLGameObject*> (m_gameObjects[i])))
			{
				TheGame::Instance()->getStateMachine()->pushState(new GameOverState());
				break;
			}
		}

		m_gameObjects[i]->update();
	}	

	/*if (checkCollision(dynamic_cast<SDLGameObject*> (m_gameObjects[0]), dynamic_cast<SDLGameObject*> (m_gameObjects[1])))
		TheGame::Instance()->getStateMachine()->pushState(new GameOverState());

	if (checkCollision(dynamic_cast<SDLGameObject*> (m_gameObjects[0]), dynamic_cast<SDLGameObject*> (m_gameObjects[2])))
		TheGame::Instance()->getStateMachine()->pushState(new GameOverState());

	if (checkCollision(dynamic_cast<SDLGameObject*> (m_gameObjects[0]), dynamic_cast<SDLGameObject*> (m_gameObjects[3])))
		TheGame::Instance()->getStateMachine()->pushState(new GameOverState());*/
}

void PlayState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
		m_gameObjects[i]->draw();
}

bool PlayState::onEnter()
{
	StateParser stateParser;

	stateParser.parseState("Datadrivenjson.json", s_playID, &m_gameObjects, &m_textureIDList);

	std::cout << "Entering PlayState\n";

	return true;
}

bool PlayState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
		m_gameObjects[i]->clean();

	m_gameObjects.clear();

	// clear the texture manager
	for (int i = 0; i < m_textureIDList.size(); i++)
		TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);

	std::cout << "exiting PlayState" << std::endl;
	return true;
}

bool PlayState::checkCollision(SDLGameObject* p1, SDLGameObject* p2)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = p1->getPosition().getX();
	rightA = p1->getPosition().getX() + p1->getWidth();
	topA = p1->getPosition().getY();
	bottomA = p1->getPosition().getY() + p1->getHeight();

	leftB = p2->getPosition().getX();
	rightB = p2->getPosition().getX() + p2->getWidth();
	topB = p2->getPosition().getY();
	bottomB = p2->getPosition().getY() + p2->getHeight();

	if (bottomA <= topB) { return false; }
	if (topA >= bottomB) { return false; }
	if (rightA <= leftB+25) { return false; }
	if (leftA >= rightB-25) { return false; }
	return true;
}
