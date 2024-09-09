#pragma once

#include <string>
#include <map>

#include "json.hpp"
#include "GameObject.h"

#ifndef __BaseCreator__
#define __BaseCreator__

class BaseCreator
{
public:
	virtual GameObject* createGameObject() const = 0;
	virtual ~BaseCreator() {}
};

#endif // __BaseCreator__

#ifndef __GameObjectFactory__
#define __GameObjectFactory__

class GameObjectFactory
{
public:

	static GameObjectFactory* Instance()
	{
		if (s_pInstance == nullptr)
			s_pInstance = new GameObjectFactory();

		return s_pInstance;
	}

	bool registerTyoe(std::string typeID, BaseCreator* pCreator)
	{
		std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);

		if (it != m_creators.end())
		{
			delete pCreator;
			return false;
		}

		m_creators[typeID] = pCreator;
		return true;
	}

	GameObject* create(std::string typeID)
	{
		std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);

		if (it == m_creators.end())
		{
			std::cout << "Could not find type: " << typeID << std::endl;
			return NULL;
		}

		BaseCreator* pCreator = (*it).second;
		return pCreator->createGameObject();
	}

private:
	std::map<std::string, BaseCreator*> m_creators;

	static GameObjectFactory* s_pInstance;
};

#endif // __GameObjectFactory__
