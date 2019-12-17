#include "GameEngine.h"
#include "GameObject.h"
#include "MoveScript.h"
#include "GridManager.h"
#include <ctime>

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

// Scene 1°³
void GameEngine::mainLoop() {

	auto& objs = GameObject::gameObjects;

	//srand(time(nullptr));
	rand();

	GameObject* map = new GameObject("map", nullptr, "map", "", Vector2{ 20, 10 });
	GameObject::Add(map); //wrapping
	map->addComponent<GridManager>();
	auto gm = static_cast<GridManager *> (map->getComponent<GridManager>());

	GameObject* monster = new GameObject("monster", map, "monster", "m", Vector2{ rand()%gm->getWidth(), rand()%gm->getHeight() });
	monster->addComponent<MoveScript>();
	GameObject::Add(monster);
	
	GameObject* ghost = new GameObject("ghost", map, "ghost", "g", Vector2{ rand() % gm->getWidth(), rand() % gm->getHeight() });
	ghost->addComponent<MoveScript>();
	GameObject::Add(ghost);

	for (int i = 0; i < 20; i++) {
		string name = "food(" + to_string(i);
		name += ")";
		GameObject *food = new GameObject(name, map, "food", "#", Vector2{ rand() % gm->getWidth(), rand() % gm->getHeight() });
		objs.push_back(food);
	}


	for (auto obj : objs)
	{
		obj->traverseStart();
	}

	while (!Input::GetKeyDown(KeyCode::Esc)) {
		screen.clear();
		// update		
		for (auto obj : objs)
		{
			obj->traverseUpdate();
		}
		// erase in active objects

		// draw

		screen.render();
		Sleep(100);

		Input::EndOfFrame();
	}

	while (objs.size()) {
		auto obj = objs.back();
		objs.pop_back();
		delete obj;
	}

	return;
}