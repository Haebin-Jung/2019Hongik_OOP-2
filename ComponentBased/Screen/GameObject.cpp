#include "GameObject.h"


/* STATIC VARIABLES and FUNCTIONS */
vector<GameObject*> gameObjects;

GameObject* GameObject::Find(const string& name)
{
	for (auto obj : gameObjects) {
		if (obj->name == name)	return obj;
		else return nullptr;
	}
}

//참조할 클래스 포함
#include "Component.h"
#include "Transform.h"


GameObject::GameObject(const string& name, GameObject* parent = nullptr, const string& tag = "")
	: name(name), parent(parent), tag(tag), enabled(true),
	transform(new Transform) // Transform에서의 생성자 함수 필요
{
	components.clear();
	components.push_back(transform);
}

GameObject::~GameObject() {}

void GameObject::traverse() {
		if (enabled == false) return;

		for (auto comp : components) {
			comp->doUpdate(comp);
			//포인터 변수의 protected 멤버함수 접근이 금지되어 있어 만든 함수입니다.
		}
		for (auto child : children) {
			child->traverse();
		}
}
