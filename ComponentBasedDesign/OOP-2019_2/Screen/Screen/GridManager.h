#pragma once
#include "Component.h"
#include "Utils.h"
class GridManager :
	public Component
{
	int width;
	int height;
	Screen& screen;
public:
	GridManager(GameObject* gameObject);
	~GridManager();

	int getWidth() const { return width; }		// 값이 바뀌지 않는 함수임
	int getHeight() const { return height; }	// 값이 바뀌지 않는 함수임

	void resideInside(Vector2& pos);

protected:
	void start();
	void update();
};

