#pragma once
#include "Utils.h"
#include <string>

//상호참조할 클래스 전방선언
class GameObject;


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