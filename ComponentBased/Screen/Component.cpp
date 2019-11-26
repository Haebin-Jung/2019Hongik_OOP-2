#pragma once
#include "Component.h"

using namespace std;

//������ Ŭ���� ����
#include "GameObject.h"
#include "Transform.h"


Component::Component(GameObject* gameObject)
	: gameObject(gameObject),
	transform(gameObject->getTransform())
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