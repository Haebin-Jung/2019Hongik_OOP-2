#include "GameObject.h"
#include "BlockScript.h"



BlockScript::BlockScript(GameObject* gameObject)
	: Component(gameObject), tr(nullptr),
	blockNum(rand()%8+1), rotation(0), 
	collision(false), movable(true), //width(1), height(1),
	screen(Screen::getInstance())
{
	tr = static_cast<Transform *> (gameObject->getComponent<Transform>());
	rotateBlock(blockNum, rotation);
}


BlockScript::~BlockScript()
{
}

void BlockScript::rotateBlock(int blockNum, int rotation) {
	if (gameObject == nullptr || !movable) return;
	string &shape = tr->getShape(gameObject);

	switch (blockNum)
	{
	case 1: // I Block
		if (rotation == 0 || rotation == 2) {
			shape = "\xB2   \xB2   \xB2   \xB2   ";
			width = 1;
			height = 4;
		}
		else {
			shape = "\xB2\xB2\xB2\xB2            ";
			width = 4;
			height = 1;
		}
		break;
	case 2: // J
		if (rotation == 0) {
			shape = " \xB2   \xB2  \xB2\xB2      ";
			width = 2;
			height = 3;
		}
		else if (rotation == 1) {
			shape = "\xB2\xB2\xB2   \xB2         ";
			width = 3;
			height = 2;
		}
		else if (rotation == 2) {
			shape = "\xB2\xB2  \xB2   \xB2       ";
			width = 2;
			height = 3;
		}
		else {
			shape = "\xB2   \xB2\xB2\xB2         ";
			width = 3;
			height = 2;
		}
		break;
	case 3: // L
		if (rotation == 0) {
			shape = "\xB2   \xB2   \xB2\xB2      ";
			width = 2;
			height = 3;
		}
		else if (rotation == 1) {
			shape = "  \xB2 \xB2\xB2\xB2         ";
			width = 3;
			height = 2;
		}
		else if (rotation == 2) {
			shape = "\xB2\xB2   \xB2   \xB2      ";
			width = 2;
			height = 3;
		}
		else {
			shape = "\xB2\xB2\xB2 \xB2           ";
			width = 3;
			height = 2;
		}
		break;
	case 4: // O
			shape = "\xB2\xB2  \xB2\xB2          ";
			break;
	case 5: // S
		if (rotation == 0 || rotation == 3) {
			shape = " \xB2\xB2 \xB2\xB2          ";
			width = 3;
			height = 2;
		}
		else {
			shape = "\xB2   \xB2\xB2   \xB2      ";
			width = 2;
			height = 3;
		}
		break;
	case 6: // T
		if (rotation == 0) {
			shape = "\xB2\xB2\xB2  \xB2          ";
			width = 3;
			height = 2;
		}
		else if (rotation == 1) {
			shape = "\xB2   \xB2\xB2  \xB2       ";
			width = 2;
			height = 3;
		}
		else if (rotation == 2) {
			shape = " \xB2  \xB2\xB2\xB2         ";
			width = 3;
			height = 2;
		}
		else {
			shape = " \xB2  \xB2\xB2   \xB2      ";
			width = 2;
			height = 3;
		}
		break;
	case 7: // Z
		if (rotation == 0 || rotation == 3) {
			shape = "\xB2\xB2   \xB2\xB2         ";
			width = 3;
			height = 2;
		}
		else {
			shape = " \xB2  \xB2\xB2  \xB2       ";
			width = 2;
			height = 3;
		}
		break;
	}
	return;
}

bool BlockScript::checkCollision(Transform* transform) {
	Vector2 pos = transform->getPosition();
	string shape = transform->getShape(gameObject);
	bool isBlock = true; // �ش� �ε����� ����̸� true
	int idx = 0;
	while (idx < shape.size() + 1 && !collision) {
		// �ش� �ε����� ��Ұ� NULL�̸� ���� �ε��� Ȯ��
		if (shape[idx] == NULL) {
			isBlock = false;
			continue;
		}
		isBlock = true;
		
		// �ش� �ε����� ��Ұ� ����� ���
		// ���� �ε����� ���̸� ���� �浹Ȯ��
		if (!isBlock) {
			movable = isCollided(pos.X() + (idx % 4), pos.Y() + (idx / 4));
		}

		// �ش� �ε��� ���� �Ʒ��� ����� ������ �浹Ȯ��
		if (idx + 4 == NULL) {
			collision = isCollided(pos.X() + (idx % 4), pos.Y() + (idx / 4) + 1);
		}

		// ���� �ε����� ���̸� ������ �浹Ȯ��
		if (idx + 1 == NULL) {
			collision = isCollided(pos.X() + (idx % 4) + 1, pos.Y() + (idx / 4) + 1);
			idx++; // �������� �ε��� Ȯ��
		}

	}
	if (collision) { 
		return true; 
	}
	else return false;
}

bool BlockScript::isCollided(float x, float y) {
	Vector2 pos = { x, y };
	char col = screen.getScreenInfo(pos);
	// �ش� ��ǥ�� ��ü�� ������ false, ������ true
	if (col == NULL)
		return false;
	else {
		return true;
	}
}