#pragma once
#include "Component.h"
class GridScript :
	public Component
{
	int width;
	int height;
public:
	GridScript(GameObject* gameObject);
	~GridScript();

protected:
	void start();

	void update();
};

