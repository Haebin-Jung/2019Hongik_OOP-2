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

	void setPosition(const Vector2& pos) { position = pos; }
	Vector2 getPosition() const { return position; }

protected:
	void start();

	void update();
};

