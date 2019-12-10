#pragma once
#include "Component.h"
#include "Utils.h"

using namespace std;

class Transform :
	public Component
{
	Vector2 position;
	Vector2 rotation;
	Vector2 scale;
	string shape;

	Screen& screen;

public:
	Transform(GameObject* gameObject,
		const string& shape = "", // Empty string
		const Vector2& position = Vector2::zero,
		const Vector2& rotation = Vector2::zero,
		const Vector2& scale = Vector2::ones);

	~Transform();

protected:
	void start();

	void update();
};

