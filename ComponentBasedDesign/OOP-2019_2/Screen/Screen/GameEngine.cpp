#include "GameEngine.h"
#include "GameObject.h"
#include "MoveScript.h"
#include "GridManager.h"
#include "BlockScript.h"
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

// Scene 1��
void GameEngine::mainLoop() {

	auto& objs = GameObject::gameObjects; //gameObjects��� ���Ϳ� ����� GameObject���� �����Ͱ�ü

	srand(time(nullptr));

	// ��Ʈ���� �� ����
	GameObject* map = new GameObject("map", nullptr, "map", "", Vector2{ 1, 1 });
	map->addComponent<GridManager>();

	// ������� ȭ�� ����
	GameObject* next = new GameObject("next", nullptr, "next", "", Vector2{ 15, 1 });
	next->addComponent<GridManager>();
	auto gm = static_cast<GridManager *> (next->getComponent<GridManager>());
	gm->resizeGrid(10, 4);

	int nblocks = 0;
	GameObject* block = new GameObject("block", map, "block", "\xB2", Vector2{ gm->getWidth() / 2, 1 });
	block->addComponent<BlockScript>();
	block->addComponent<MoveScript>();
	GameObject::Add(block);
	
	GameObject::Add(next);
	GameObject::Add(map);


	for (auto obj : objs)
	{
		obj->traverseStart();
	}

	while (!Input::GetKeyDown(KeyCode::Esc)) {
		screen.clear();
		// update	
		nblocks = 0;

		// Ȱ���� ��� ��ü Ȯ��
		for (auto obj : objs) {
			BlockScript* bs = static_cast<BlockScript*> (obj->getComponent<BlockScript>());
			if (bs == nullptr) continue;
			if (obj->getTag() == "block" && bs->canMove()) {
				nblocks++;
				break;
			}
		}

		// Ȱ���� ����� ������ �� ��� ����
		if (nblocks == 0) {
			GameObject* block = new GameObject("block", map, "block", "\xB2", Vector2{ gm->getWidth() / 2, 1 });
			block->addComponent<BlockScript>();
			block->addComponent<MoveScript>();
			GameObject::Insert(block);
			block->traverseStart();
		}


		for (auto obj : objs)
		{
			obj->traverseUpdate();
		}
		// erase in active objects

		// draw

		screen.render();
		Sleep(300);

		Input::EndOfFrame();
	}

	while (objs.size()) {
		auto obj = objs.back();
		objs.pop_back();
		delete obj;
	}

	return;
}