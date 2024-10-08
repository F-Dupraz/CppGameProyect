#include <fstream>
#include <iostream>

#define JSON_TRY_USER if(true)
#define JSON_CATCH_USER(exception) if(false)
#define JSON_THROW_USER(exception)                           \
    {std::clog << "Error in " << __FILE__ << ":" << __LINE__ \
               << " (function " << __FUNCTION__ << ") - "    \
               << (exception).what() << std::endl;           \
     std::abort();}

#include "StateParser.h"
#include "GameObjectFactory.h"
#include "Game.h"

using json = nlohmann::json;

bool StateParser::parseState(const char* stateFile, std::string stateID, std::vector<GameObject*>* pObjects, std::vector<std::string>* pTextureIDs)
{
	json jsonDoc;

	std::ifstream i("./Datadrivenjson.json");

	jsonDoc = json::parse(i);

	json pRoot = jsonDoc["States"];

	json pStateRoot = NULL;

	for (int i = 0; i < pRoot.size(); ++i)
	{
		if (pRoot[i].is_null())
			break;

		if (pRoot[i]["StateID"] == stateID)
		{
			pStateRoot = pRoot[i];
			break;
		}
	}

	json pTextureRoot = pStateRoot["Textures"];

	parseTextures(pTextureRoot, pTextureIDs);

	json pObjectRoot = pStateRoot["Objects"];

	parseObjects(pObjectRoot, pObjects);

	return true;
}

void StateParser::parseTextures(json pStateRoot, std::vector<std::string>* pTextureIDs)
{
	for (int i = 0; i < pStateRoot.size(); ++i)
	{
		std::string filenameAtribute = pStateRoot[i]["filename"];
		std::string idAtribute = pStateRoot[i]["ID"];
		pTextureIDs->push_back(idAtribute);

		TheTextureManager::Instance()->load(filenameAtribute, idAtribute, TheGame::Instance()->getRenderer());
	}
}

void StateParser::parseObjects(json pStateRoot, std::vector<GameObject*>* pObjects)
{
	for (int i = 0; i < pStateRoot.size(); ++i)
	{
		int x, y, width, height, numFrames, callbackID, animSpeed;

		x = pStateRoot[i]["x"];
		y = pStateRoot[i]["y"];
		width = pStateRoot[i]["width"];
		height = pStateRoot[i]["height"];
		numFrames = pStateRoot[i]["numFrames"];
		callbackID = pStateRoot[i]["callbackID"];
		animSpeed = pStateRoot[i]["animSpeed"];

		std::string textureID = pStateRoot[i]["textureID"];

		GameObject* pGameObject = GameObjectFactory::Instance()->create(pStateRoot[i]["type"]);
		pGameObject->load(new LoaderParams(x, y, width, height, textureID, numFrames, callbackID, animSpeed));
		pObjects->push_back(pGameObject);
	}
}
