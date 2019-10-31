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
#include <ctime>
#include <random>

using namespace std;

class GameObject {
	bool		enabled;

protected:

	Position	pos;
	Screen&		screen;
	char*		shape;
	int			width;
	int			height;

	vector<GameObject *> children;
	GameObject*	parent;

public:
	GameObject(const char* shape, int width, int height, const Position& pos = Position{ 0, 0 })
		: height(height), width(width), shape(nullptr), pos(pos), enabled(true), parent(nullptr),
		screen(Screen::getInstance()) {
		if (!shape || strlen(shape) == 0)
			this->shape = nullptr;
		else {
			this->shape = new char[width*height];
			strncpy(this->shape, shape, width*height);
		}
		children.clear();
	}

	GameObject(int width, int height, const Position& pos = Position{ 0, 0 })
		: GameObject(nullptr, width, height, pos)
	{}

	virtual ~GameObject()
	{
		while (children.size() > 0) {
			auto back = children.back();
			children.pop_back();
			delete back;
		}
		if (shape) { delete[] shape; }
		shape = nullptr;
		width = 0, height = 0;
	}

	void setParent(GameObject* parent) {
		this->parent = parent;
	}

	void add(GameObject* child) {
		if (!child) return;

		child->setParent(this);
		children.push_back(child);
	}

	virtual bool isActive() { return enabled; }

	void setActive(bool flag = true) { enabled = flag; }

	void setShape(const char* shape) {
		if (!shape) return;
		strncpy(this->shape, shape, width*height);
	}

	virtual void setPos(int x, int y) { this->pos.x = x; this->pos.y = y; }

	int getWidth() const { return width; }
	int getHeight() const { return height; }

	Position& getPos() { return pos; }

	vector<GameObject *>& getChildren() {
		return children;
	}

	void internalDraw(const Position& inheritedPos = Position{ 0, 0 }) {
		if (!enabled) return;

		draw(inheritedPos);

		for (auto& child : children) child->internalDraw(pos + inheritedPos);
	}

	virtual void draw(const Position& inheritedPos = Position{ 0, 0 }) {
		screen.draw(shape, width, height, pos + inheritedPos);
	}

	void internalUpdate() {
		if (!enabled) return;
		update();
		for (auto& child : children) child->internalUpdate();
	}

	virtual void update() {}

	static const char rect = '\xb1';
};


class Panel : public GameObject {

public:
	Panel(const char* layout, int width, int height, const Position& pos) : GameObject(layout, width, height, pos) {}

	GameObject* pop() {
		auto& children = getChildren();
		auto back = children.back();
		children.pop_back();
		back->setParent(nullptr);
		return back;
	}

	void draw(const Position& inheritedPos) {
		screen.drawRect(Position{ pos.x - 1, pos.y - 1 } +inheritedPos, getWidth() + 2, getHeight() + 2);
	}
};

class Text : public Panel {

public:
	Text(const char* info, const Position& pos) : Panel(info, strlen(info), 1, pos) {}

	void draw(const Position& inheritedPos) {
		screen.draw(shape, width, 1, pos + inheritedPos);
	}
};

class Item : public Text {
	int items;
	char* buf;

public:
	Item(const Position& pos, int total = 0) : Text("Remaining Items:     ", pos), items(total) {
		buf = new char[strlen(shape) + 1];
	}

	~Item() {
		delete[] buf;
	}

	//void addScore(int inc) {
	//	if (inc < 0) return;
	//	score += inc;
	//}

	void decTotal(int dec) {
		if (dec < 0) return;
		items -= dec;
	}

	int total() {
		return items;
	}

	void draw(const Position& inheritedPos) {
		sprintf(buf, "Remaining Items: %3d", items);
		screen.draw(buf, strlen(buf), 1, pos + inheritedPos);
	}
};

class Map : public Panel {
	bool* map;
	int   width;
	int	  height;
	char* buffer;
	Item* items;
	int numOfItems;

public:
	Map(int width, int height, const Position& pos)
		: map(new bool[width*height]), width(width), height(height), buffer(new char[width*height+1]),
		Panel(nullptr, width, height, pos), items(nullptr), numOfItems(0)
	{
		for (int i = 0; i < width*height; i++)
		{
			map[i] = false;
		}
		memset(buffer, NULL, sizeof(buffer));
	}

	~Map() {
		if (map) delete[] map;
		if (buffer) delete[] buffer;
	}

	void setItems(int items) {
		numOfItems = items;
	}

	void decNumOfItems(int items) {
		if (this->items) this->items->decTotal(items);
	}

	bool isOpened(Position pos) {
		if (map[pos.x-1 + (pos.y-1)*width])
			return true;
		else {
			map[pos.x-1 + (pos.y-1)*width] = true;
			return false;
		}
	}

	bool isDone() {
		int reItems = numOfItems; //남은 아이템의 개수
		for (int i = 0; i < width*height; i++) {
			if (map[i] == false) return false;
			if (reItems < 0) break;
			reItems--;
		}
		//if (reItems < 0) return true;
		//else return false;
		return true;
	}
	
	void place(const char* shape, const Position& pos, int w, int h) {
		map[(pos.x-1) + (pos.y-1)*width] = true;
		decNumOfItems(1);
	}

	void draw(const Position& inheritedPos)
	{
		screen.drawRect(Position{ pos.x - 1, pos.y - 1 } +inheritedPos, width + 2, height + 2);
		for (int i = 0; i < width*height; i++) {
			if (map[i]) buffer[i] = '-';
			else buffer[i] = GameObject::rect;;
		}
		buffer[width*height+1] = '\0';
		screen.draw(buffer, width, height, Position{ pos.x, pos.y } +inheritedPos);
		
	}
};

struct MonsterShape {
	const string shape[5] = { "\xe4", "\x89", "\x8e", "\x99", "\x9A" };
	const string name[5] = { "몬스터", "도깨비", "외계인", "우주인", "슬라임" };
	int width;
	int height;
};

class Monster : public GameObject {
	float x;
	float y;
	const string* name;
	int items;
	int steps;
	Map map;
	bool isAlive;
	bool move;

public:
	Monster(const string name, const string shape, Map& map, const Position& pos = Position{ 0, 0 })
		: GameObject(shape.c_str(), 1, 1, pos), x(.0f), y(.0f),
		items(0), steps(0), map(map), isAlive(true), move(false)
	{ }

	void setPos(int x, int y) {
		GameObject::setPos(x, y);
	}
	
	void moveAround(Map *map, Position pos) {
		random_device randNum;
		Position prePos;
		prePos.x = pos.x;
		prePos.y = pos.y;
		while (!move) {
			switch (randNum() % 8)
			{
			case 0:
				pos.x--; pos.y--; break;
			case 1:
				pos.y--; break;
			case 2:
				pos.x++; pos.y--; break;
			case 3:
				pos.x--; break;
			case 4:
				pos.x++; break;
			case 5:
				pos.x--; pos.y++; break;
			case 6:
				pos.y++; break;
			case 7:
				pos.x++; pos.y++; break;
			}
			if (pos.x < 1 || pos.y < 1 || pos.x > parent->getWidth() || pos.y > parent->getHeight()) {
				pos.x = prePos.x;
				pos.y = prePos.y;
			}
			else {
				move = true;
				this->pos.x = pos.x;
				this->pos.y = pos.y;
				steps++;
			}
		}
		return;
	}

	void eat(Position pos) {
		if (!map.isOpened(pos)) {
			items++;
		}
		return;
	}

	int numOfSteps() {
		return steps;
	}

	void update() {
		if (isActive() == false) return;
		move = false;

		moveAround(&map, this->pos);
		eat(this->pos);

		//if (Input::GetKeyDown(KeyCode::Right)) {
		//	x++;
		//	if (parent) {
		//		if (x + width >= parent->getWidth()) x = parent->getWidth() - width;
		//	}
		//	else {
		//		if (x + width >= screen.getWidth()/2) x = screen.getWidth() - width;
		//	}
		//}
		//if (Input::GetKeyDown(KeyCode::Left)) {
		//	x--;
		//	if (x < 0.0f) x = 0.0f;
		//}
		//if (Input::GetKeyDown(KeyCode::Up)) {
		//	rotateShape();
		//}
		//if (Input::GetKeyDown(KeyCode::Down)) {
		//	speed *= 2;
		//}			
		//if (Input::GetKeyDown(KeyCode::Space)) {
		//	if (map) {
		//		pos.y = y;
		//		while (!map->isGrounded(shape, pos, width, height)) {
		//			pos.y++; y+= 1.0f;
		//		}
		//		return;
		//	}
		//}
		//if (Input::GetKeyDown(KeyCode::A)) {
		//	rotateShape();
		//}
		//y += speed;
	}

	void draw(const Position& inheritedPos) {

		screen.draw(shape, width, height, pos + inheritedPos);
	}
};

int main()
{
	Screen&	 screen = Screen::getInstance();
	vector<GameObject *> gameObjects;
	vector<Monster *> monsters;
	MonsterShape mShape;

	std::system("chcp 437");

	auto mainMap = new Map(30, 15, Position{ 1, 1 });
	mainMap->setItems(mainMap->getWidth() * mainMap->getHeight());
	auto& children = mainMap->getChildren();
	int numOfMonsters = monsters.size();
	int numOfSteps = 0;

	auto statePanel = new Panel(nullptr, mainMap->getWidth(), 3 + 5, Position{ 1, mainMap->getHeight() + 1 });
	statePanel->add(new Text("Total movement : ", Position{ 1, 1 }));
	auto items = new Item(Position{ 1, 2 }, mainMap->getWidth() * mainMap->getHeight() / 2);
	statePanel->add(items);

	gameObjects.push_back(mainMap);

	auto mon1 = new Monster(mShape.name[0], mShape.shape[0], *mainMap, Position{ 2,2 });
	mon1->setParent(mainMap);
	auto mon2 = new Monster(mShape.name[1], mShape.shape[1], *mainMap, Position{ 10,5 });
	mon2->setParent(mainMap);
	auto mon3 = new Monster(mShape.name[2], mShape.shape[2], *mainMap, Position{ 20,10 });
	mon3->setParent(mainMap);
	auto mon4 = new Monster(mShape.name[3], mShape.shape[3], *mainMap, Position{ 29,13 });
	mon4->setParent(mainMap);
	auto mon5 = new Monster(mShape.name[4], mShape.shape[4], *mainMap, Position{ 12,14 });
	mon5->setParent(mainMap);

	gameObjects.push_back(mon1);
	monsters.push_back(mon1);
	gameObjects.push_back(mon2);
	monsters.push_back(mon2);
	gameObjects.push_back(mon3);
	monsters.push_back(mon3);
	gameObjects.push_back(mon4);
	monsters.push_back(mon4);
	gameObjects.push_back(mon5);
	monsters.push_back(mon5);

	gameObjects.push_back(statePanel);

	screen.clear(); screen.render();

	while (!mainMap->isDone()) {
		Borland::gotoxy(0,0);
		screen.clear();
		for (auto obj : gameObjects) { obj->internalUpdate(); }
		for (auto obj : monsters) { 
			numOfSteps += obj->numOfSteps(); 
			//Borland::gotoxy()
		}

		for (auto it = gameObjects.cbegin();
			it != gameObjects.cend(); it++)
			(*it)->internalDraw();

		screen.render();
		Sleep(500);

		Input::EndOfFrame();
	}
	Borland::gotoxy(statePanel->getWidth()/3, statePanel->getPos().y+statePanel->getHeight());
	printf("게임종료");

	while (gameObjects.size() > 0) {
		auto back = gameObjects.back();
		gameObjects.pop_back();
		delete back;
	}

	return 0;
}