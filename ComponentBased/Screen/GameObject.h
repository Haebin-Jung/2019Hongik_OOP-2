#pragma once
#pragma once
#include "Component.h"
#include <string>
#include <vector>
using namespace std;



class Component;
class Transform;
class GameEngine;
class GameObject : public Component
{
private:
	bool		enabled;
	string		name;
	string		tag;
	GameObject* parent;

	static vector<GameObject*> gameObjects;
	vector<Component*> components;
	Transform* transform;
	friend class GameEngine;

public:
	GameObject(const string& name, GameObject* parent, const string& tag);

	~GameObject();

	void traverse();

	Transform* getTransform();

	static GameObject* Find(const string& name);

	void setParent(GameObject* parent);

	virtual bool isActive();

	void setActive(bool flag);
};
