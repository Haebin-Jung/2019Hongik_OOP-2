#pragma once
#include "Component.h"
#include "Utils.h"

//상호참조할 클래스 전방선언
class Component;
class GameObject;


class Transform : public Component {
private:
	Vector2 position;
	Vector2 rotation; //Quaternion
	Vector2 scale;

	Component* component;

protected:
	void start();
	void update();

public:
	Transform(GameObject* gameObject,
		const Vector2& position = Vector2::zero,
		const Vector2& rotation = Vector2::zero,
		const Vector2& scale = Vector2::one);
};
