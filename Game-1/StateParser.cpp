#include <fstream>

#include "StateParser.h"
#include "GameObjectFactory.h"
#include "Game.h";

using json = nlohmann::json;

bool StateParser::parseState(const char* stateFile, std::string stateID, std::vector<GameObject*>* pObjects, std::vector<std::string>* pTextureIDs)
{
	json jsonDoc;

	std::ifstream i("./Datadrivenjson.json");

	jsonDoc = json::parse(i);
	std::cout << jsonDoc << std::endl << std::endl << std::endl;

	json pRoot = jsonDoc["States"];
	std::cout << pRoot << std::endl << std::endl << std::endl;

	json pStateRoot = NULL;

	for (int i = 0; i < sizeof(pRoot); ++i)
	{
		if (pRoot[i] == NULL)
			break;

		std::cout << pRoot[i] << std::endl << std::endl << std::endl;

		std::cout << pRoot[i]["StateID"] << std::endl << std::endl << std::endl;

		if (pRoot[i]["StateID"] == stateID)
			pStateRoot = pRoot[i];
	}

	json pTextureRoot = pStateRoot["Textures"];
	std::cout << pTextureRoot << std::endl << std::endl << std::endl;

	parseTextures(pTextureRoot, pTextureIDs);

	json pObjectRoot = pStateRoot["Objects"];
	std::cout << pObjectRoot << std::endl << std::endl << std::endl;

	parseObjects(pObjectRoot, pObjects);

	return true;
}

void StateParser::parseTextures(json pStateRoot, std::vector<std::string>* pTextureIDs)
{
	for (int i = 0; i < sizeof(pStateRoot); ++i)
	{
		std::string filenameAtribute = pStateRoot[i]["filename"];
		std::cout << filenameAtribute << std::endl;
		std::string idAtribute = pStateRoot[i]["ID"];
		std::cout << idAtribute << std::endl;
		pTextureIDs->push_back(idAtribute);
		TheTextureManager::Instance()->load(filenameAtribute, idAtribute, TheGame::Instance()->getRenderer());
	}
}

void StateParser::parseObjects(json pStateRoot, std::vector<GameObject*>* pObjects)
{
	for (int i = 0; i < sizeof(pStateRoot); ++i)
	{
		int x, y, width, height, numFrames, callbackID, animSpeed;

		x = pStateRoot[i]["x"];
		std::cout << x << std::endl;
		y = pStateRoot[i]["y"];
		std::cout << 7 << std::endl;
		width = pStateRoot[i]["width"];
		std::cout << width << std::endl;
		height = pStateRoot[i]["height"];
		std::cout << height << std::endl;
		numFrames = pStateRoot[i]["numFrames"];
		std::cout << numFrames << std::endl;
		callbackID = pStateRoot[i]["callbackID"];
		std::cout << callbackID << std::endl;
		animSpeed = pStateRoot[i]["animSpeed"];
		std::cout << animSpeed << std::endl;

		std::string textureID = pStateRoot[i]["textureID"];

		GameObject* pGameObject = GameObjectFactory::Instance()->create(pStateRoot[i]["type"]);
		pGameObject->load(new LoaderParams(x, y, width, height, textureID, numFrames, callbackID, animSpeed));
		pObjects->push_back(pGameObject);
	}
}
