#pragma once
#include "Component.h"

//������ Ŭ���� ����
#include "Transform.h"
#include "GameObject.h"


Component::Component(GameObject* gameObject)
{}

Component::~Component() {}

void Component::awake() {}
void Component::onEnable() {}
void Component::start() {}
void Component::fixedUpdate() {}
void Component::update() {}
void Component::lateUpdate() {}
void Component::onDisable() {}
void Component::onDeestroy() {}

void Component::doUpdate(Component* comp) { comp->update(); }


Component* Component::GetComponent(string type)
{
	for (auto comp : compList) {
		if (comp->compName == type) {
			return comp;
		}
	}
}

Component Component::AddComponent(string className, Component* component)
{
	// className�� ������Ʈ�� �ִ��� Ȯ��


	// �̹� �ִ� ������Ʈ�� �߰����� ����
	for (auto comp : components) {
		if (comp->compName == className)
			return NULL;
	}

	//������Ʈ ���� �߰�
	components.push_back(component);
}

GameObject* Component::getGameObjectInfo(GameObject* obj)
{
	return obj = gameObject;
}