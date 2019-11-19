// Screen.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
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

class GameObject;
class Transform;

class Component {
	GameObject* gameObject;
	Transform* transform;

public:
	Component(GameObject* gameObject) 
		: gameObject(gameObject),
		transform(gameObject->getTransform())
	{}

	// 객체를 저장할 때는 컴포넌트로 upCasting하여 저장하지만, 사용할때는 downCasting하여 쓴다.
	// 상속받는 클래스가 upCasting하여 저장할 때, 소멸을 시킬 경우 원본 클래스의 소멸자가 호출되는 메커니즘
	virtual ~Component() {}

protected: //private도 괜찮다.
	virtual void awake() {}
	virtual void onEnable() {}
	virtual void start() {}
	virtual void fixedUpdate() {}
	virtual void update() {}
	virtual void lateUpdate() {}
	virtual void onDisable() {}
	virtual void onDeestroy() {}

};

class MyScript : public Component {
protected:
	// C#의 경우 override 키워드를 사용한다.
	void start() 
	{

	}

	void update() 
	{

	}
};

class Transform : public Component {

};

// Component에서 업데이트 함
// GameObject : 자신의 정보를 담는 최소한의 그릇(깡통)!
class GameObject {
	bool		enabled;
	string		name;	// unique identifier
	string		tag;	// class의 역할
	GameObject* parent;
	// 원본복사 방지를 위해 포인터 변수 사용
	// 레퍼런스를 사용하지 않는 이유는 한번 setting이 되면 바꿀 수 없기 때문
	// Unity에서는 Map을 사용하는 것으로 짐작됨
	vector<Component *> componets;

	static vector<GameObject*> gameObjects;

	Transform* transform;

// protected의 경우 getter setter함수 쓰기

public:
	//클래스형 자료형은 그대로 넘기지 말고 반드시 레퍼런스나 포인터로 넘겨야 한다.
	//하이라키 뷰에 등록되는 게임오브젝트
	GameObject(const string& name, GameObject* parent=nullptr, const string& tag="")
		: name(name), parent(parent), tag(tag), enabled(true),
		transform(new Transform ) {
		componets.clear();
		componets.push_back(transform); // 멤버변수(게임객체)에 등록하고, 컴포넌트에 등록한다.
	}

	// Component에게 상속을 받는 모델이기 때문에 가상소멸자가 굳이 필요하진 않다
	~GameObject()
	{

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

/*

int main()
{
	Screen&	 screen = Screen::getInstance();
	vector<GameObject *> gameObjects;

	string mode = "mode con cols=" + to_string(screen.getWidth() + 10);
	mode += " lines=" + to_string(screen.getHeight() + 5);

	std::system(mode.c_str());
	std::system("chcp 437");

	screen.clear(); screen.render();
	
	while (!Input::GetKeyDown(KeyCode::Esc)) {
		screen.clear();
		// update

		// erase in active objects

		//draw
				
		screen.render();		
		Sleep(100);		

		Input::EndOfFrame();		
	}

	return 0;
}*/