// 2019 ȫ�ʹ��б� 2�г� 2�б� ��ü�������α׷���(2) ����
// 2019 Honik Univ. OOP(2) class
// Component-based Design
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <array>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include "Utils.h"

using namespace std;


// Component�� ���� �߻����� ǥ��, ��ü�� ����� ����� ���� �߻�ü, �߻�Ŭ����(Abstract Class)��� �Ѵ�.
// ���������Լ�(pure virtual function)�� virtual �Լ��� �����ϰ� body�� ����. == �Լ� �ּҸ� ������ �������� ����.(nullptr�� ����Ų��)
// ���������Լ��� ���� Ŭ������ ���� ������ �� ����.
// Abstract method�θ� ������ �Լ� == Interface
// Interface�� ������ ����(implement)�ϴ� �� == �Լ� body�� ����� ��
class GameObject;
class Transform;
class Component {
private:
	Transform* transform;

public:
	Component(GameObject* gameObject) 
		: gameObject(gameObject),
		transform(gameObject->getTransform())
	{}
	//���������Լ��� �������ϴµ� c++������ ���� �����Ǵ� Ű���尡 ����.
	// C#, Java�� ���  Ŭ������ �տ� abstract Ű���带 ����ϸ� �߻�Ŭ������ ���� �� �ִ�.

	virtual ~Component() {}
	// ��ü�� ������ ���� ������Ʈ�� Up Casting�Ͽ� ����������, ����Ҷ��� Down Casting�Ͽ� ����.
	// ��ӹ޴� Ŭ������ Up Casting�Ͽ� ������ ��, �Ҹ��� ��ų ��� ���� Ŭ������ �Ҹ��ڰ� ȣ��Ǵ� ��Ŀ����

protected:
	GameObject* gameObject;
	virtual void awake() {}
	virtual void onEnable() {}
	virtual void start() {}
	virtual void fixedUpdate() {}
	virtual void update() {}
	virtual void lateUpdate() {}
	virtual void onDisable() {}
	virtual void onDeestroy() {}
	// virtual void onDeestroy() = 0; ���������Լ��� ��
	// ��ӵ� Ŭ���������� �ݵ�� �Լ� body�� ����� ����Ѵ�

};

//class MyScript : public Component {
//protected:
//	// C#�� ��� override Ű���带 ����Ѵ�.
//	void start() 
//	{
//
//	}
//
//	void update() 
//	{
//
//	}
//};

class Transform : public Component {

	Vector2 position;
	Vector2 rotation; //Quaternion
	Vector2 scale;

public:
	Transform(GameObject* gameObject, const Vector2& position = Vector2::zero,
		const Vector2& rotation = Vector2::zero, const Vector2& scale = Vector2::one)
		: position(position), rotation(rotation), scale(scale),
		Component(gameObject) //�ڽ��� �θ� Ŭ������ �������Լ� ȣ��. C++�� ��� ���߻�Ӹ��̱� ������ �θ�������Լ��� ���� ȣ���ؾ��Ѵ�. C#���� base, Java���� super�� ȣ���Ѵ�.
	{}

protected:
	void start() {}
	void update() {}
};

class GameEngine;

// GameObject : �ڽ��� ������ ��� �ּ����� �׸�(����)!
class GameObject : public Component {
	bool		enabled;
	string		name;	// unique identifier
	string		tag;	// class�� ����
	GameObject* parent;
	// �������� ������ ���� ������ ���� ���
	// ���۷����� ������� �ʴ� ������ �ѹ� setting�� �Ǹ� �ٲ� �� ���� ����
	// Unity������ Map�� ����ϴ� ������ ���۵�
	vector<Component *> components;

	friend class GameEngine;
	// friend �������� ���ӿ��� Ŭ�������� gameObjects�� ���ٰ���

	static vector<GameObject*> gameObjects;
	// Ŭ������ ȣ����� �ʾƵ� ��ü�� �����ؾ� �ϹǷ� ���� ��ü������ �������� ���ǵǾ��־�� �Ѵ�.

	Transform* transform;

	// protected�� ��� getter setter�Լ� ����
public:
	// Ŭ������ �ڷ����� �״�� �ѱ��� ���� �ݵ�� ���۷����� �����ͷ� �Ѱܾ� �Ѵ�.
	// ���̶�Ű �信 ��ϵǴ� ���ӿ�����Ʈ
	GameObject(const string& name, GameObject* parent=nullptr, const string& tag="")
		: name(name), parent(parent), tag(tag), enabled(true),
		transform(new Transform( gameObject, Vector2::zero, Vector2::zero, Vector2::one)),
		Component(gameObject)
	{
		components.clear();
		components.push_back(transform); // �������(���Ӱ�ü)�� ����ϰ�, ������Ʈ�� ����Ѵ�.
	}

	// Component���� ����� �޴� ���̱� ������ ����Ҹ��ڰ� ���� �ʿ����� �ʴ�
	~GameObject()
	{

	}
	
	void traverse() {
		if (enabled == false) return;

		//for (auto comp : components) {
		//	comp->Component::update();
		//}
		//for (auto child : children) {
		//	child->traverse();
		//}
	}

	Transform* getTransform() {
		return transform;
	}

	// ���� ���ӿ�����Ʈ ��ü���� ã�°� �ƴ� ��ü ���ӿ�����Ʈ ����Ʈ���� ã�⶧���� static���� �����Ѵ�
	static GameObject* Find(const string& path) {

	}

	void setParent(GameObject* parent) {
		this->parent = parent;
	}

	//��ǻ� Getter()
	virtual bool isActive() { return enabled;  }
	//��ǻ� Setter()
	void setActive(bool flag = true) { enabled = flag;  }
};

vector<GameObject*> GameObject::gameObjects;
// ���������� ��� �Ҽ������� ����Ͽ� ����

class GameEngine {
	Screen& screen;

	static GameEngine* instance;

	GameEngine() : screen(Screen::getInstance()) {
		string mode = "mode con cols=" + to_string(screen.getWidth() + 10);
		mode += " lines=" + to_string(screen.getHeight() + 5);

		std::system(mode.c_str());
		std::system("chcp 437");

		screen.clear(); screen.render();
	}
public:
	static GameEngine& getInstance();

	void mainLoop() {
		//for (auto obj : GameObject::gameObjects)
		//{
		//	obj->traverseAwake();
		//}
		//for (auto obj : GameObject::gameObjects)
		//{
		//	obj->traverseOnEnable();
		//}
		//for (auto obj : GameObject::gameObjects)
		//{
		//	obj->traverseStart();
		//}

		while (!Input::GetKeyDown(KeyCode::Esc)) {
			screen.clear();
			//// update
			//for (auto obj : GameObject::gameObjects)
			//{
			//	obj->traverseFixedUpdate();
			//}
			//for (auto obj : GameObject::gameObjects)
			//{
			//	obj->traverseUpdate();
			//}
			//for (auto obj : GameObject::gameObjects)
			//{
			//	obj->traverseLateUpdate();
			//}

			//// erase in active objects

			////draw
			//for (auto obj : GameObject::gameObjects)
			//{
			//	obj->traversePreDraw();
			//}
			//for (auto obj : GameObject::gameObjects)
			//{
			//	obj->traverseDraw();
			//}
			//for (auto obj : GameObject::gameObjects)
			//{
			//	obj->traversePostDraw();
			//}

			screen.render();
			Sleep(100);

			Input::EndOfFrame();
		}
		//for (auto obj : GameObject::gameObjects) {
		//	obj->startOnDisable();
		//}
		//for (auto obj : GameObject::gameObjects) {
		//	obj->startOnDestroy();
		//}
		return;
	}
};

GameEngine* GameEngine::instance = nullptr;

GameEngine& GameEngine::getInstance() {
	if (instance == nullptr) {
		instance = new GameEngine();
	}
	return *instance;
}

int main()
{
	GameEngine& engine = GameEngine::getInstance();

	engine.mainLoop();	

	return 0;
}