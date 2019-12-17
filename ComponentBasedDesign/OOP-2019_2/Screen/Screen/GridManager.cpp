#include "GridManager.h"
#include "GameObject.h"
#include "Transform.h"



GridManager::GridManager(GameObject* gameObject)
	: Component(gameObject), screen(Screen::getInstance()),
	width(10), height(10), gameObjects(GameObject::GetGameObjects())
{
}


GridManager::~GridManager()
{
}

void GridManager::start() {		// 값 초기화
	width = 10;
	height = 10;
}

void GridManager::update() {
	//정확히는 GridRenderer를 만들고 그곳에서 처리해야 함
	screen.drawRect(Vector2{ 0.0f,0.0f }, width + 1, height + 1);
}

void GridManager::resideInside(Vector2& pos) {
	int x = pos.X();
	int y = pos.Y();
	if (x < 0) pos.x = 0;
	else if (x > width-1) pos.x = width - 1;
	if (y < 0) pos.y = 0;
	else if (y > height-1) pos.y = height - 1;
}

void GridManager::removeVictims(const GameObject& predator) {
	// 스캔가능하지만 수정 불가능, GameObject에게 삭제를 요청해야함
	//auto obj = ;//remove할 오브젝트가 여러개일 때를 고려해야함
	GameObject* obj = nullptr;
	auto predatorPos = const_cast<GameObject*>(&predator)->getTransform()->getPosition(); //const를 non-const로 변환
	for (auto it = gameObjects.cbegin(); it != gameObjects.cend(); it++) {
		auto item = *it;
		auto name = item->getName();
		size_t pos = name.find("food(");

		if (pos == string::npos) continue;
		auto itemPos = (item->getTransform())->getPosition();
		if (predatorPos.X() == itemPos.X() && predatorPos.Y() == itemPos.Y()) {
			obj = item;
			break;
		}
		//predator와 it을 통해 나온 gameObject가 같은 위치에 있으면 삭제!
	}
	if (obj == nullptr) return;
	GameObject::Remove(obj);
}