#pragma once
#include "Component.h"
#include "Utils.h"
#include <vector>

class GridManager :
	public Component
{
	bool isGameOver;
	int width;
	int height;

	Screen& screen;
	const vector<GameObject*>& gameObjects;
public:
	GridManager(GameObject* gameObject);
	~GridManager();

	int getWidth() const { return width; }			// 너비반환 함수
	int getHeight() const { return height; }		// 높이반환 함수

	void resideInside(Vector2& pos, int w, int h);				// 이동제한 부가 함수

	void resizeGrid(int w, int h);

	float getBottom();

	//void removeLines();							// 라인 제거 함수
protected:
	void start();
	void update();
};

