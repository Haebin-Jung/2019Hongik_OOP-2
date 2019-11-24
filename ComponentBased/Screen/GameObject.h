#pragma once
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

	Component* component;
	Transform* transform;

	static vector<GameObject*> gameObjects;
	static vector<GameObject*> children;
	vector<Component*> components;
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

	void attachType(string typeName);
};
