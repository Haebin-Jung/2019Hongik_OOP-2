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

	vector<GameObject*> children;

	static vector<GameObject *> gameObjects;
	friend class GameEngine;

	Transform* transform;

public:
	GameObject(const string& name, 
		GameObject* parent = nullptr, 
		const string& tag = "",
		const Vector2& position = Vector2::zero,
		const Vector2& rotation = Vector2::zero,
		const Vector2& scale = Vector2::ones);

	~GameObject();

	template<typename T>
	void addComponent();

	template<typename T>
	T* getComponent();

	void traverseStart();
	void traverseUpdate();

	Transform* getTransform() { return transform; }

	static GameObject* Find(const string& path);

	void setParent(GameObject* parent) 
	{this->parent = parent;}

	virtual bool isActive() 
	{ return enabled; }

	void setActive(bool flag = true) 
	{ enabled = flag; }

};

