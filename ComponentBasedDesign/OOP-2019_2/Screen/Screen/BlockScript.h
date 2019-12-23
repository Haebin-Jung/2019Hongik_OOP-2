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
	int blockNum;	// 블록을 구분하는 번호
	int rotation;	// 회전상태
	int width;		// 실제 블록의 너비
	int height;		// 실제 블록의 높이

	bool collision;	// 충돌체크 : 충돌하면 true
	bool movable;	// 이동체크 : 플레이어가 좌 또는 우로 움직일 수 있으면 true

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

