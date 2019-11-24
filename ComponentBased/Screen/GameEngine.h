#pragma once
#include "Utils.h"
#include <string>

//��ȣ������ Ŭ���� ���漱��
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