// Screen.cpp : �� ���Ͽ��� 'main' �Լ��� ���Ե˴ϴ�. �ű⼭ ���α׷� ������ ���۵ǰ� ����˴ϴ�.
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
	Component() {}
	virtual ~Component() {}
};

class Transform : public Component {

};

// Component���� ������Ʈ ��
// GameObject : �ڽ��� ������ ��� �ּ����� �׸�(����)!
class GameObject {
	bool		enabled;
	string		name;	// unique identifier
	string		tag;	// class�� ����
	GameObject* parent;
	// �������� ������ ���� ������ ���� ���
	// ���۷����� ������� �ʴ� ������ �ѹ� setting�� �Ǹ� �ٲ� �� ���� ����
	// Unity������ Map�� ����ϴ� ������ ���۵�
	vector<Component *> componets;

	static vector<GameObject*> gameObjects;

	Transform* transform;

// protected�� ��� getter setter�Լ� ����

public:
	GameObject() {

	}

	// Component���� ����� �޴� ���̱� ������ ����Ҹ��ڰ� ���� �ʿ����� �ʴ�
	~GameObject()
	{

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