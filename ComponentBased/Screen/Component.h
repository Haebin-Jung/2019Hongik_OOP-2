#include "GameObject.h"
#pragma once
class Component {
public:
	Component(GameObject* gameObject) {}
	virtual ~Component() {}

protected:
	GameObject* gameObject;
	virtual void awake() {}
	virtual void onEnable() {}
	virtual void start() {}
	virtual void fixedUpdate() {}
	virtual void update() {}
	virtual void lateUpdate() {}
	virtual void onDisable() {}
	virtual void onDeestroy() {}
	// virtual void onDeestroy() = 0; 순수가상함수의 예
	// 상속된 클래스에서는 반드시 함수 body를 만들어 줘야한다

};
