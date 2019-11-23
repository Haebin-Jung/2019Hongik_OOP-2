#pragma once
#include "GameObject.h"
#include "Transform.h"



class GameObject;
class Transform;
class Component {
private:
	Transform* transform;

protected:
	GameObject* gameObject;

	virtual void awake();
	virtual void onEnable();
	virtual void start();
	virtual void fixedUpdate();
	virtual void update();
	virtual void lateUpdate();
	virtual void onDisable();
	virtual void onDeestroy();

public:
	Component(GameObject* gameObject);

	virtual ~Component();

	void doUpdate(Component* comp);
};
