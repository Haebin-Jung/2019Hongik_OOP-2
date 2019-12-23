#pragma once
#include "Component.h"
#include "GridManager.h"

class BlockScript;

class MoveScript :
	public Component
{
	GridManager* gm;
	BlockScript* bs;
	
public:
	MoveScript(GameObject* gameObject);
	~MoveScript();

	void start();

	void update();

	void dropBlock(Vector2& pos);	// ����� ����߸��� �޼ҵ�
	void move(Vector2& pos);
};