#include "GameEngine.h"
#include "GameObject.h"
#include "MoveScript.h"

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

// Scene 1개
void GameEngine::mainLoop() {

	auto& objs = GameObject::gameObjects;

	GameObject map("map");
	objs.push_back(&map);
	// map의 경우, Stack에 쌓인 지역변수이기 때문에 동적해제를 하는 방식으로 처리할 경우 Error발생 소지가 있음
	
	GameObject monster("monster", &map);
	monster.addComponent<MoveScript>();
	objs.push_back(&monster);
	
	GameObject ghost("ghost", &map);
	monster.addComponent<MoveScript>();
	objs.push_back(&ghost);

	for (int i = 0; i < 20; i++) {
		string name = "food(" + i;
		name += ")";
		GameObject *food = new GameObject(name, &map);
		objs.push_back(food);
	}


	for (auto obj : objs)
	{
		obj->traverseStart();
	}

	while (!Input::GetKeyDown(KeyCode::Esc)) {
		//screen.clear();
		// update		
		for (auto obj : objs)
		{
			obj->traverseUpdate();
		}
		// erase in active objects

		// draw

		//screen.render();
		Sleep(100);

		Input::EndOfFrame();
	}
	return;
}