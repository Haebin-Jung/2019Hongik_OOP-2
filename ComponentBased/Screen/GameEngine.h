#pragma once
#include <iostream>
#include <string>


//��ȣ������ Ŭ���� ���漱��
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