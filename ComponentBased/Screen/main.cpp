// 2019 홍익대학교 2학년 2학기 객체지향프로그래밍(2) 수업
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


// Component와 같이 추상적인 표현, 실체로 만들기 어려운 것을 추상객체, 추상클래스(Abstract Class)라고 한다.
// 순수가상함수(pure virtual function)는 virtual 함수를 선언하고 body는 없다. == 함수 주소만 가지고 가진것은 없다.(nullptr를 가리킨다)
// 순수가상함수를 가진 클래스는 직접 생성할 수 없다.
// Abstract method로만 구성된 함수 == Interface
// Interface를 가져와 구현(implement)하는 것 == 함수 body를 만드는 것
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
	//순수가상함수로 만들어야하는데 c++에서는 따로 제공되는 키워드가 없다.
	// C#, Java의 경우  클래스명 앞에 abstract 키워드를 사용하면 추상클래스를 만들 수 있다.

	virtual ~Component() {}
	// 객체를 저장할 때는 컴포넌트로 Up Casting하여 저장하지만, 사용할때는 Down Casting하여 쓴다.
	// 상속받는 클래스가 Up Casting하여 저장할 때, 소멸을 시킬 경우 원본 클래스의 소멸자가 호출되는 메커니즘

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
	// virtual void onDeestroy() = 0; 순수가상함수의 예
	// 상속된 클래스에서는 반드시 함수 body를 만들어 줘야한다

};

//class MyScript : public Component {
//protected:
//	// C#의 경우 override 키워드를 사용한다.
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
		Component(gameObject) //자신의 부모 클래스의 생성자함수 호출. C++의 경우 다중상속모델이기 때문에 부모생성자함수를 직접 호출해야한다. C#에선 base, Java에선 super로 호출한다.
	{}

protected:
	void start() {}
	void update() {}
};

class GameEngine;

// GameObject : 자신의 정보를 담는 최소한의 그릇(깡통)!
class GameObject : public Component {
	bool		enabled;
	string		name;	// unique identifier
	string		tag;	// class의 역할
	GameObject* parent;
	// 원본복사 방지를 위해 포인터 변수 사용
	// 레퍼런스를 사용하지 않는 이유는 한번 setting이 되면 바꿀 수 없기 때문
	// Unity에서는 Map을 사용하는 것으로 짐작됨
	vector<Component *> components;

	friend class GameEngine;
	// friend 선언으로 게임엔진 클래스에서 gameObjects에 접근가능

	static vector<GameObject*> gameObjects;
	// 클래스가 호출되지 않아도 실체가 존재해야 하므로 따로 객체변수가 전역으로 정의되어있어야 한다.

	Transform* transform;

	// protected의 경우 getter setter함수 쓰기
public:
	// 클래스형 자료형은 그대로 넘기지 말고 반드시 레퍼런스나 포인터로 넘겨야 한다.
	// 하이라키 뷰에 등록되는 게임오브젝트
	GameObject(const string& name, GameObject* parent=nullptr, const string& tag="")
		: name(name), parent(parent), tag(tag), enabled(true),
		transform(new Transform( gameObject, Vector2::zero, Vector2::zero, Vector2::one)),
		Component(gameObject)
	{
		components.clear();
		components.push_back(transform); // 멤버변수(게임객체)에 등록하고, 컴포넌트에 등록한다.
	}

	// Component에게 상속을 받는 모델이기 때문에 가상소멸자가 굳이 필요하진 않다
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

	// 현재 게임오브젝트 자체에서 찾는게 아닌 전체 게임오브젝트 리스트에서 찾기때문에 static으로 선언한다
	static GameObject* Find(const string& path) {

	}

	void setParent(GameObject* parent) {
		this->parent = parent;
	}

	//사실상 Getter()
	virtual bool isActive() { return enabled;  }
	//사실상 Setter()
	void setActive(bool flag = true) { enabled = flag;  }
};

vector<GameObject*> GameObject::gameObjects;
// 전역변수가 어느 소속인지도 명시하여 선언

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