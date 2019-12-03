#pragma once
#include "Component.h"
class MoveScript :
	public Component
{
public:
	MoveScript(GameObject* gameObject);
	~MoveScript();

	void start();

	void update();
};

