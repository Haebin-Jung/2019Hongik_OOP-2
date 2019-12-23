#pragma once
#include "Component.h"
#include "GridManager.h"
#include "Transform.h"
#include "MoveScript.h"
#include "Utils.h"

enum blockNumber {
	I = 1,
	J,
	L,
	O,
	S,
	T,
	Z
};

class BlockScript :
	public Component
{
	int blockNum;	// ����� �����ϴ� ��ȣ
	int rotation;	// ȸ������
	int width;		// ���� ����� �ʺ�
	int height;		// ���� ����� ����

	bool collision;	// �浹üũ : �浹�ϸ� true
	bool movable;	// �̵�üũ : �÷��̾ �� �Ǵ� ��� ������ �� ������ true

	Transform* tr;
	Screen& screen;

	friend class MoveScript;
public:
	BlockScript(GameObject* gameObject);
	~BlockScript();

	void rotateBlock(int blockNum, int rotation);

	bool checkCollision(Transform* transform);

	bool isCollided(float x, float y);

	bool canMove() { return movable; }

	int getBlockWidth() { return width; }
	int getBlockHeight() { return height; }
};

