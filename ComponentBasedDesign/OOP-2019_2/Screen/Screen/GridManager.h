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

	int getWidth() const { return width; }			// �ʺ��ȯ �Լ�
	int getHeight() const { return height; }		// ���̹�ȯ �Լ�

	void resideInside(Vector2& pos, int w, int h);				// �̵����� �ΰ� �Լ�

	void resizeGrid(int w, int h);

	float getBottom();

	//void removeLines();							// ���� ���� �Լ�
protected:
	void start();
	void update();
};

