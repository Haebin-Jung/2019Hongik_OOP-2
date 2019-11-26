#pragma once
#include "Component.h"

using namespace std;

//참조할 클래스 선언
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
	// className의 컴포넌트가 있는지 확인


	// 이미 있는 컴포넌트면 추가하지 않음
	for (auto comp : components) {
		if (comp->compName == className)
			return NULL;
	}

	//컴포넌트 새로 추가
	components.push_back(component);
}

GameObject* Component::getGameObjectInfo(GameObject* obj)
{
	return obj = gameObject;
}