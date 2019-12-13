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

	int getWidth() const { return width; }		// ���� �ٲ��� �ʴ� �Լ���
	int getHeight() const { return height; }	// ���� �ٲ��� �ʴ� �Լ���

	void resideInside(Vector2& pos);

protected:
	void start();
	void update();
};

