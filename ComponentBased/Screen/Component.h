#pragma once
#include <vector>
#include <string>
using namespace std;
//클래스 상호참조로 인한 오류 발생

//상호참조할 클래스 전방선언
class Transform;
class GameObject;


class Component {
private:
	string compName;
	Transform* transform;
	//추가할 수 있는 컴포넌트 목록
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