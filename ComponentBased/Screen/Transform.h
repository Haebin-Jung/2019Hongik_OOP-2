#pragma once
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
	Transform(GameObject* gameObject, const Vector2& position,
		const Vector2& rotation, const Vector2& scale);
};
