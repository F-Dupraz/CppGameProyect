#include "GameState.h"
#include "TextureManager.h"

bool GameState::onExit()
{
	for (size_t i = 0; i < m_textureIDList.size(); ++i)
		TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);

	return true;
}