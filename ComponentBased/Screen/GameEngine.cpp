#pragma once
#include "GameEngine.h"

using namespace std;

//참조할 클래스 포함
#include "GameObject.h"
#include "Utils.h"

/* STATIC VARIABLES and FUNCTIONS */
GameEngine* GameEngine::instance = nullptr;

GameEngine& GameEngine::getInstance() {
	if (instance == nullptr) {
		instance = new GameEngine();
	}
	return *instance;
}


GameEngine::GameEngine() : screen(Screen::getInstance()) {
		string mode = "mode con cols=" + to_string(screen.getWidth() + 10);
		mode += " lines=" + to_string(screen.getHeight() + 5);

		std::system(mode.c_str());
		std::system("chcp 437");

		screen.clear(); screen.render();
	}

void GameEngine::mainLoop() {
		
		for (auto obj : GameObject::gameObjects)
		{
			//obj->traverseStart();
		}

		while (!Input::GetKeyDown(KeyCode::Esc)) {
			screen.clear();
			// update
			for (auto obj : GameObject::gameObjects)
			{
				//obj->traverseUpdate();
			}
			// erase in active objects

			//draw
			
			screen.render();
			Sleep(100);

			Input::EndOfFrame();
		}
		return;
	}

