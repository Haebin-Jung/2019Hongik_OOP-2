#pragma once
#include "GameEngine.h"

//참조할 클래스 포함
#include "GameObject.h"


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
			//obj->traverseAwake();
		}
		for (auto obj : GameObject::gameObjects)
		{
			//obj->traverseOnEnable();
		}
		for (auto obj : GameObject::gameObjects)
		{
			//obj->traverseStart();
		}

		while (!Input::GetKeyDown(KeyCode::Esc)) {
			screen.clear();
			// update
			for (auto obj : GameObject::gameObjects)
			{
				//obj->traverseFixedUpdate();
			}
			for (auto obj : GameObject::gameObjects)
			{
				//obj->traverseUpdate();
			}
			for (auto obj : GameObject::gameObjects)
			{
				//obj->traverseLateUpdate();
			}

			// erase in active objects

			//draw
			for (auto obj : GameObject::gameObjects)
			{
				//obj->traversePreDraw();
			}
			for (auto obj : GameObject::gameObjects)
			{
				//obj->traverseDraw();
			}
			for (auto obj : GameObject::gameObjects)
			{
				//obj->traversePostDraw();
			}

			screen.render();
			Sleep(100);

			Input::EndOfFrame();
		}
		for (auto obj : GameObject::gameObjects) {
			//obj->startOnDisable();
		}
		for (auto obj : GameObject::gameObjects) {
			//obj->startOnDestroy();
		}
		return;
	}

GameEngine* GameEngine::instance = nullptr;

GameEngine& GameEngine::getInstance() {
	if (instance == nullptr) {
		instance = new GameEngine();
	}
	return *instance;
}