#include "GameObject.h"




GameObject::GameObject(const string& name, GameObject* parent = nullptr, const string& tag = "")
		: name(name), parent(parent), tag(tag), enabled(true),
		transform(new Transform(gameObject, Vector2::zero, Vector2::zero, Vector2::one)),
		Component(gameObject)
	{
		components.clear();
		components.push_back(transform);
	}

GameObject::~GameObject()
	{

	}

void GameObject::traverse() {
		if (enabled == false) return;

		for (auto comp : components) {
			doUpdate(comp);
			//������ ������ protected ����Լ� ������ �����Ǿ� �־� ���� �Լ��Դϴ�.
		}
		//for (auto child : children) {
		//	child->traverse();
		//}
}

Transform* GameObject::getTransform() { return transform; }

GameObject* GameObject::Find(const string& name)
{ 
	for (auto obj : gameObjects) {
		if (obj->name == name)	return obj;
		else return nullptr;
	}
}

void GameObject::setParent(GameObject* parent) { this->parent = parent; }

bool GameObject::isActive() { return enabled; }

void GameObject::setActive(bool flag = true) { enabled = flag; }