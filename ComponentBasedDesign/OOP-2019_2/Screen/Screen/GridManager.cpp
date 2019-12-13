#include "GridManager.h"



GridManager::GridManager(GameObject* gameObject)
	: Component(gameObject), screen(Screen::getInstance()),
	width(40), height(20)
{
}


GridManager::~GridManager()
{
}

void GridManager::start() {		// �� �ʱ�ȭ
	width = 40;
	height = 20;
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