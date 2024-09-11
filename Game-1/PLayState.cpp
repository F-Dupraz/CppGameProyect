#include <string>
#include <iostream>

#include "PlayState.h"
#include "PauseState.h"
#include "GameOver.h"
#include "InputHandler.h"
#include "Game.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
		TheGame::Instance()->getStateMachine()->pushState(new PauseState());

	for (int i = 0; i < m_gameObjects.size(); i++)
		m_gameObjects[i]->update();

	if (checkCollision(dynamic_cast<SDLGameObject*> (m_gameObjects[0]), dynamic_cast<SDLGameObject*> (m_gameObjects[1])))
		TheGame::Instance()->getStateMachine()->pushState(new GameOverState());

	if (checkCollision(dynamic_cast<SDLGameObject*> (m_gameObjects[0]), dynamic_cast<SDLGameObject*> (m_gameObjects[2])))
		TheGame::Instance()->getStateMachine()->pushState(new GameOverState());

	if (checkCollision(dynamic_cast<SDLGameObject*> (m_gameObjects[0]), dynamic_cast<SDLGameObject*> (m_gameObjects[3])))
		TheGame::Instance()->getStateMachine()->pushState(new GameOverState());
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

	if (!TheTextureManager::Instance()->load("./Images/pixil-frame-1.png", "Enemy1", TheGame::Instance()->getRenderer()))
		return false;

	//GameObject* player = new Player(new LoaderParams((720 / 2), 100, 85, 100, "PlayerT", 5));
	//GameObject* enemy_1 = new Enemy(new LoaderParams(620, 400, 85, 100, "Enemy1", 5));
	//GameObject* enemy_2 = new Enemy(new LoaderParams(520, 500, 85, 100, "Enemy1", 5));
	//GameObject* enemy_3 = new Enemy(new LoaderParams(420, 600, 85, 100, "Enemy1", 5));

	/*m_gameObjects.push_back(player);
	m_gameObjects.push_back(enemy_1);
	m_gameObjects.push_back(enemy_2);
	m_gameObjects.push_back(enemy_3);*/

	std::cout << "entering PlayState\n";
	return true;
}

bool PlayState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
		m_gameObjects[i]->clean();

	m_gameObjects.clear();

	TheTextureManager::Instance()->clearFromTextureMap("PlayerT");
	TheTextureManager::Instance()->clearFromTextureMap("Enemy1");

	std::cout << "exiting PlayState\n";
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

	if (bottomA <= (topB+10)) { return false; }
	if (topA >= (bottomB-10)) { return false; }
	if (rightA <= (leftB+25)) { return false; }
	if (leftA >= (rightB-25)) { return false; }
	return true;
}
