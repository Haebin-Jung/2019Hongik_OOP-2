#pragma once
#include "Component.h"
#include "GridManager.h"
class MoveScript :
	public Component
{
	GridManager* gm;
public:
	MoveScript(GameObject* gameObject);
	~MoveScript();

	void start();

	void update();
};

