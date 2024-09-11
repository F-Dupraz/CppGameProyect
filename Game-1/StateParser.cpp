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

	std::cout << jsonDoc << std::endl;
	
	return true;
}
