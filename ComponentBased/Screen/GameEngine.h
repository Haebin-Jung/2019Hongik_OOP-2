#pragma once
#include <iostream>
#include <string>


//상호참조할 클래스 전방선언
class Screen;
class Input;

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