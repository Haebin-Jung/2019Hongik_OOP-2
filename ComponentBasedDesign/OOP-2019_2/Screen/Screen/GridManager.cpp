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

void GridManager::start() {		// �� �ʱ�ȭ
	width = 10;
	height = 10;
}

void GridManager::update() {
	//��Ȯ���� GridRenderer�� ����� �װ����� ó���ؾ� ��
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
	// ��ĵ���������� ���� �Ұ���, GameObject���� ������ ��û�ؾ���
	//auto obj = ;//remove�� ������Ʈ�� �������� ���� ����ؾ���
	GameObject* obj = nullptr;
	auto predatorPos = const_cast<GameObject*>(&predator)->getTransform()->getPosition(); //const�� non-const�� ��ȯ
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
		//predator�� it�� ���� ���� gameObject�� ���� ��ġ�� ������ ����!
	}
	if (obj == nullptr) return;
	GameObject::Remove(obj);
}