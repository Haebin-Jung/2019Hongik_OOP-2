#pragma once
#include "Utils.h"
#include "GameObject.h"
#include <string>

class GameEngine
{
private:
	Screen& screen;
	static GameEngine* instance;

	GameEngine();
public:
	static GameEngine& getInstance();

	void mainLoop();
};