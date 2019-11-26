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

//������ Ŭ���� ����
#include "Component.h"
#include "Transform.h"


GameObject::GameObject(const string& name, GameObject* parent = nullptr, const string& tag = "")
	: name(name), parent(parent), tag(tag), enabled(true),
	transform(new Transform) // Transform������ ������ �Լ� �ʿ�
{
	components.clear();
	components.push_back(transform);
}

GameObject::~GameObject() {}

void GameObject::traverse() {
		if (enabled == false) return;

		for (auto comp : components) {
			comp->doUpdate(comp);
			//������ ������ protected ����Լ� ������ �����Ǿ� �־� ���� �Լ��Դϴ�.
		}
		for (auto child : children) {
			child->traverse();
		}
}
