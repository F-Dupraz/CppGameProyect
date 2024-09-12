#include "MainMenuState.h"
#include "StateParser.h"

const std::string MainMenuState::s_menuID = "MENU";

bool MainMenuState::onEnter()
{
	StateParser stateParser;

	std::cout << "Entramos al MainMenuState!\n";

	stateParser.parseState("Datadrivenjson.json", s_menuID, &m_gameObjects, &m_textureIDList);

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_menuToPlay);
	m_callbacks.push_back(s_exitFromMenu);

	setCallbacks(m_callbacks);

	std::cout << "Entering MenuState\n";

	return true;
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