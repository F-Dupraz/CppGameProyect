#pragma once

#ifndef __StateParser__
#define __StateParser__

#include <iostream>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class GameObject;

class StateParser
{
public:
	bool parseState(const char* stateFile, std::string stateID, std::vector<GameObject*>* pObjects, std::vector<std::string>* pTextureIDs);

private:
	void parseObjects(json pStateRoot, std::vector<GameObject*>* pObjects);
	void parseTextures(json pStateRoot, std::vector<std::string>* pTextureIDs);
};

#endif // __StateParser__
