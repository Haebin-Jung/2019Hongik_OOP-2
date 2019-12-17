#pragma once
#include "Component.h"
#include "Utils.h"
#include <vector>

class GridManager :
	public Component
{
	int width;
	int height;
	Screen& screen;
	const vector<GameObject*>& gameObjects;
public:
	GridManager(GameObject* gameObject);
	~GridManager();

	int getWidth() const { return width; }		// 값이 바뀌지 않는 함수임
	int getHeight() const { return height; }	// 값이 바뀌지 않는 함수임

	void resideInside(Vector2& pos);

	void removeVictims(const GameObject& predator);
protected:
	void start();
	void update();
};

