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
	// virtual void onDeestroy() = 0; ���������Լ��� ��
	// ��ӵ� Ŭ���������� �ݵ�� �Լ� body�� ����� ����Ѵ�

};
