#include "GridManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "BlockScript.h"



GridManager::GridManager(GameObject* gameObject)
	: Component(gameObject), screen(Screen::getInstance()),
	width(10), height(20), isGameOver(false),
	gameObjects(GameObject::GetGameObjects())
{
}


GridManager::~GridManager()
{
}

void GridManager::start() 
{	
}

void GridManager::update() {
	screen.drawRect(
		Vector2{ transform->getPosition().X()-1, 
		transform->getPosition().Y()-1 }, 
		width + 3, 
		height + 3); // 테두리가 되는 사각형을 그리기
	return;
}

void GridManager::resideInside(Vector2& pos, int w, int h) {

	int x = pos.X();
	int y = pos.Y();

	if (x < transform->getPosition().X()) pos.x = transform->getPosition().X();
	else if (x + w > transform->getPosition().X() + width) pos.x = transform->getPosition().X() + width - w+1;
	
	if (y < transform->getPosition().Y()) {
		isGameOver = true;
	}
	else if (y + h > transform->getPosition().Y() + height) pos.y = transform->getPosition().Y() + height - h+1;
	
	return;
}


void GridManager::resizeGrid(int w, int h) {
	width = w;
	height = h;
	return;
}

float GridManager::getBottom() {
	return transform->getPosition().Y() + height + 1;
}

//void GridManager::removeLines() {
//	// 스캔가능하지만 수정 불가능, GameObject에게 삭제를 요청해야함
//	//auto obj = ;//remove할 오브젝트가 여러개일 때를 고려해야함
//	GameObject* obj = nullptr;
//	auto predatorPos = const_cast<GameObject*>(&predator)->getTransform()->getPosition(); //const를 non-const로 변환
//	for (auto it = gameObjects.cbegin(); it != gameObjects.cend(); it++) {
//		auto item = *it;
//		auto name = item->getName();
//		size_t pos = name.find("food(");
//
//		if (pos == string::npos) continue;
//		auto itemPos = (item->getTransform())->getPosition();
//		if (predatorPos.X() == itemPos.X() && predatorPos.Y() == itemPos.Y()) {
//			obj = item;
//			break;
//		}
//		//predator와 it을 통해 나온 gameObject가 같은 위치에 있으면 삭제!
//	}
//	if (obj == nullptr) return;
//	GameObject::Remove(obj);
//}