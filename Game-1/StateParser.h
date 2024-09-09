#pragma once

#ifndef __StateParser__
#define __StateParser__

#include <iostream>
#include <vector>
#include <string>
#include <json.hpp>

class GameObject;

class StateParser
{
public:	
	bool parserState(const char* stateFile, std::string stateID, std::vector<GameObject*>* pObject);

private:
	void parseObjects()

};

#endif __StateParser__
