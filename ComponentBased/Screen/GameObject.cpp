#include "GameObject.h"

//������ Ŭ���� ����
#include "Component.h"
#include "Transform.h"


GameObject::GameObject(const string& name, GameObject* parent = nullptr, const string& tag = "")
	: name(name), parent(parent), tag(tag), enabled(true),
	component(new Component(this)),
	transform(new Transform(this, Vector2::zero, Vector2::zero, Vector2::one))
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

void GameObject::attachType(string typeName) { type = typeName; }