#pragma once
#include <vector>
#include <string>
using namespace std;
//Ŭ���� ��ȣ������ ���� ���� �߻�

//��ȣ������ Ŭ���� ���漱��
class Transform;
class GameObject;


class Component {
private:
	string compName;
	Transform* transform;
	//�߰��� �� �ִ� ������Ʈ ���
	static vector<Component*> compList;

protected:
	static vector<Component*> components;
	GameObject* gameObject;

	virtual void awake();
	virtual void onEnable();
	virtual void start();
	virtual void fixedUpdate();
	virtual void update();
	virtual void lateUpdate();
	virtual void onDisable();
	virtual void onDeestroy();

public:
	Component(GameObject* gameObject);

	virtual ~Component();

	void doUpdate(Component* comp);

	GameObject* getGameObjectInfo(GameObject* obj);

	Component* GetComponent(string type);
		
	Component AddComponent(string className, Component* component);
};