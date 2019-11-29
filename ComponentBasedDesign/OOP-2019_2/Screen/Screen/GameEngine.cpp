#include "GameEngine.h"
#include "GameObject.h"
#include "Utils.h"
#include "GridScript.h"

GameEngine* GameEngine::instance = nullptr;

GameEngine& GameEngine::getInstance() {
	if (instance == nullptr) {
		instance = new GameEngine();
	}
	return *instance;
}


GameEngine::GameEngine() 
	: screen(Screen::getInstance()) {
	string mode = "mode con cols=" + to_string(screen.getWidth() + 10);
	mode += " lines=" + to_string(screen.getHeight() + 5);

	std::system(mode.c_str());
	std::system("chcp 437");
	screen.clear(); screen.render();
}

void GameEngine::mainLoop() {

	GameObject map("Map");
	auto &objs = GameObject::gameObjects;
	const int maxFoods = 10;

	map.addComponent<GridScript>();

	GridScript* comp = map.getComponent<GridScript>();

	for (int i = 0; i < maxFoods; i++) {
		string name = "food(" + i;
		name += ")";
		GameObject* newObject = new GameObject(name);
		newObject->addComponent<FoodScript>();

		objs.push_back(new GameObject(name));
	}
	GameObject* monster = new GameObject("monster");
	monster->addComponent<MonsterScript>();
	GameObject* ghost = new GameObject("ghost");
	monster->addComponent<GhostScript>();

	objs.push_back(monster);
	objs.push_back(ghost);


	for (auto obj : GameObject::gameObjects)
	{
		obj->traverseStart();
	}

	while (!Input::GetKeyDown(KeyCode::Esc)) {
		screen.clear();
		// update		
		for (auto obj : GameObject::gameObjects)
		{
			obj->traverseUpdate();
		}
		// erase in active objects

		// draw

		screen.render();
		Sleep(100);

		Input::EndOfFrame();
	}
	return;
}