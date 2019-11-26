#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//상호참조할 클래스 전방선언
class Component;
class Transform;


class GameObject : public Component
{
private:
	bool		enabled;
	string		name;
	string		tag;
	GameObject* parent;
	string		type;

	Transform* transform;

	static vector<GameObject*> gameObjects;
	static vector<GameObject*> children;
	vector<Component*> components;
	friend class GameEngine;

public:
	GameObject(const string& name, GameObject* parent = nullptr, const string& tag = "");

	~GameObject();

	void traverse();

	// getter, setter 함수 등은 인라인

	Transform* getTransform() { return transform; }

	void GameObject::setParent(GameObject* parent) { this->parent = parent; }

	bool GameObject::isActive() { return enabled; }

	void GameObject::setActive(bool flag = true) { enabled = flag; }

	void GameObject::attachType(string typeName) { type = typeName; }

	static GameObject* Find(const string& name);
};