#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Utils.h"

using namespace std;

class Component;
class Transform;

class GameObject
{
	bool		enabled;
	string		name;
	string		tag;
	GameObject* parent;
	vector<Component *> components;
	vector<GameObject *> children;

	static vector<GameObject *> gameObjects;
	friend class GameEngine;

	Transform* transform;

public:
	GameObject(const string& name, GameObject* parent = nullptr, const string& tag = "", const string& shape = "", const Vector2& pos=Vector2::zero);

	~GameObject();

	void traverseStart();
	void traverseUpdate();

	string getName() const { return name; }

	Transform* getTransform() { return transform; }

	static GameObject* Find(const string& path);

	void setParent(GameObject* parent) 
	{this->parent = parent;}

	virtual bool isActive() 
	{ return enabled; }

	void setActive(bool flag = true) 
	{ enabled = flag; }

	template<typename T>
	void addComponent() {
		T t(this);
		if (dynamic_cast<Component*>(&t) == nullptr) {
			return;
		}
		components.push_back(new T(this));

		// Stack에 있는 메모리를 Heap으로 옮기는 방법? => 무브시멘틱 : &&는 문법사항일뿐
	}

	template<typename T>
	Component* getComponent() {
		for (auto comp : components)
		{
			if (dynamic_cast<T *>(comp) != nullptr) return comp;
		}
		return nullptr;
	}

};

