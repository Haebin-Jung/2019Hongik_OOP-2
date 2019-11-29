#include "GameObject.h"
#include "Transform.h"

/* STATIC VARIABLES and FUNCTIONS*/
vector<GameObject*> GameObject::gameObjects;

GameObject* GameObject::Find(const string& path) {
	return nullptr;
}

/* General variables and functions */

GameObject::GameObject(const string& name,
	GameObject* parent, const string& tag,
	const Vector2& position,
	const Vector2& rotation,
	const Vector2& scale)
	: name(name), tag(tag), enabled(true), parent(parent),
	transform(new Transform(this, position, rotation, scale)) {
	components.clear();
	components.push_back(transform);
}

GameObject::~GameObject() {}

template<typename T>
void GameObject::addComponent() // in C# where T : Component
{
	if (getComponent<T>() != nullptr) return; // 중복 허용안함
	T* newComp = new T(this);
	if (dynamic_cast<Component *>(newComp) == nullptr) {
		delete newComp;
		return;
	}

	components.push_back(newComp);
}

template<typename T>
T* GameObject::getComponent() {
	for (auto comp : components) {
		if (dynamic_cast<T*>(comp)) {//comp가 원하는 T자료형이 맞는지
			return static_cast<T*>(comp);
		}
	}
	return nullptr;
}

void GameObject::traverseStart() {
	if (enabled == false) return;

	for (auto comp : components)
	{
		comp->start();
	}
	for (auto child : children)
	{
		child->traverseStart();
	}
}

void GameObject::traverseUpdate() {
	if (enabled == false) return;

	for (auto comp : components)
	{
		comp->update();
	}
	for (auto child : children)
	{
		child->traverseUpdate();
	}
}

