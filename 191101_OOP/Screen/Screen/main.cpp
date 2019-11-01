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

	virtual bool isActive() { return enabled;  }

	void setActive(bool flag = true) { enabled = flag;  }
		
	void setShape(const char* shape) {
		if (!shape) return;
		strncpy(this->shape, shape, width*height);
	}

	virtual void setPos(int x, int y) { this->pos.x = x; this->pos.y = y; }

	int getWidth() const { return width; }
	int getHeight() const { return height;  }

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

	static const char rect = '\xB2';
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
		screen.drawRect(Position{ pos.x -1, pos.y -1 } + inheritedPos, getWidth() + 2, getHeight() + 2);
	}
};

class Text : public Panel {

public:
	Text(const char* info, const Position& pos) : Panel(info, strlen(info), 1, pos) {}

	void draw(const Position& inheritedPos) {
		screen.draw(shape, width, 1, pos + inheritedPos);
	}
};

class Score : public Text {
	int score;
	char* buf;

public:
	Score(const Position& pos) : Text("Score:     ", pos), score(0) {
		buf = new char[strlen(shape) + 1];
	}

	~Score() {
		delete[] buf;
	}

	void addScore(int inc) {
		if (inc < 0) return;
		score += inc;
	}

	void draw(const Position& inheritedPos) {
		sprintf(buf, "Score: %3d", score);
		screen.draw(buf, strlen(buf), 1, pos + inheritedPos);
	}
};

class Food : public GameObject {

public:
	Food(int x, int y, const char* shape) : GameObject(shape, 1, 1, Position{ x, y }) {}

	void getEaten() {
		setActive(false);
	}
};

class Map : public Panel {
	bool* map;
	int   width;
	int	  height;
	int   upper;
	char  buffer[100];
	Score* score;

public:
	Map(int width, int height, const Position& pos)
		: map(new bool[width*height]), width(width), height(height), upper(height - 1),
		Panel(nullptr, width, height, pos), score(nullptr)
	{
		for (int i = 0; i < width*height; i++) 
			map[i] = false;
	}

	~Map() { if (map) delete[] map; }

	void setScore(Score* score) {
		this->score = score;
	}

	void addScore(int score) {
		if (this->score) this->score->addScore(score);
	}

	bool isLineAllOccupied(int line) {
		for (int i = 0; i < width; i++) {
			if (!map[line*width + i]) {
				return false;
			}
		}
		return true;
	}

	bool evaluateLine(int line) {
		if (!isLineAllOccupied(line)) return false;

		// clean the given line
		for (int i = 0; i < width; i++) map[line*width + i] = false;

		// copy lines above the "line" down below their below lines.
		for (int i = line - 1; i >= (upper-1) && i >= 0; i--) {
			for (int j = 0; j < width; j++) 
				map[(i + 1)*width + j] = map[i*width + j];
			if (i==0) for (int i = 0; i < width; i++) 
				map[line*width + i] = false;
		}
		upper++;
		return true;
	}

	bool isGrounded(const char* shape, const Position& pos, int w, int h) {
		if (pos.y + h >= height) return true;

		// pos.y + h < height
		int next = pos.y + h;
		if (next < upper) return false;
		for (int i = 0; i < h; ++i) {
			for (int j = 0; j < w; j++)
				if (map[pos.x + j + (pos.y + i + 1) * width] && shape[j + i*w] != ' ')
					return true;
		}
		return false;
	}

	bool isOccupied(const Position& pos) {
		return map[pos.x + pos.y *width];
	}

	void place(const char* shape, const Position& pos, int w, int h) {
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				if (shape[j + i*w] != ' ')
					map[pos.x + j + (pos.y + i)* width] = true;
			}
		}
		if (pos.y < upper) upper = pos.y;
		addScore(1);
	}

	void draw(const Position& inheritedPos)
	{
		screen.drawRect(Position{ pos.x - 1, pos.y -1 } + inheritedPos, width+2, height+2);
		for (int i = upper; i < height; i++) {
			memset(buffer, ' ', 100);
			buffer[width] = '\0';
			for (int j = 0; j < width; j++) {
				if (map[j + i * width]) buffer[j] = GameObject::rect;
			}
			screen.draw(buffer, width, 1, Position{ pos.x, pos.y+ i } + inheritedPos);
		}
	}
	
	GameObject* getFood(const Position& pos) {
		for (auto child : children) {
			auto food = dynamic_cast<Food *>(child);
			if (food == nullptr) continue;
			if (food->getPos() == pos) {
				if (food->isActive() == false) continue;
				return food;
			}
		}
		return nullptr;
	}
};

class Monster : public GameObject {
	Map& map;


public:
	Monster(int x, int y, const char* shape, Map& map) : GameObject(shape, 1, 1, Position{ x, y }), map(map) {}

	void update() {
		vector<Position> targetPos{ Position{0,0},
			Position{-1,0}, Position{1,0}, Position{0,-1}, Position{0,1},
			Position{-1,-1}, Position{-1, 1}, Position{1,-1}, Position{1,1} };
		auto foodDetected = map.getFood(pos);
		if (foodDetected != nullptr){
			static_cast<Food *>(foodDetected)->getEaten();
		}
		pos += targetPos[rand() % targetPos.size()];
	}
};

int main()
{
	Screen&	 screen = Screen::getInstance();
	vector<GameObject *> gameObjects;

	string mode = "mode con cols=" + to_string(screen.getWidth() + 10);
	mode += " lines=" + to_string(screen.getHeight() + 5);

	std::system(mode.c_str());
	std::system("chcp 437");	

	auto main = new Map( 30, 15, Position{ 1, 1 });
	auto& children = main->getChildren();	

	/* TODO: 
	the following logic can share multiple foods with the same location */
	for (int i = 0; i < 50; i++) {
		main->add(new Food(rand() % main->getWidth(),
			rand() % main->getHeight(), "*"));
	}

	main->add(new Monster(rand() % main->getWidth(),
		rand() % main->getHeight(),
		"$",
		*main));

	//auto nextPanel = new Panel(nullptr, screen.getWidth() / 2-2, 10, Position{ screen.getWidth() / 2 + 1, 1 });
	//nextPanel->add(new Text("Next", Position{ 2, 4 }));
	//auto score = new Score(Position{ 2, 5 });
	//nextPanel->add(score);
	
	//main->setScore(score);

	gameObjects.push_back(main);
	//gameObjects.push_back(nextPanel);

	screen.clear(); screen.render();
	
	while (!Input::GetKeyDown(KeyCode::Esc)) {
		screen.clear();
		for (auto obj : gameObjects) obj->internalUpdate();

		bool needANewBlock = false;
		for (auto it = children.begin(); it != children.end(); ) {
			auto child = *it;
			if (child->isActive()) {
				it++;
				continue;
			}
			it = children.erase(it);
			needANewBlock = true;
		}
		
		for (auto it = gameObjects.cbegin(); 
			it != gameObjects.cend(); it++)
			(*it)->internalDraw();
				
		screen.render();		
		Sleep(100);		

		Input::EndOfFrame();		
	}
	
	while (gameObjects.size() > 0) {
		auto back = gameObjects.back();
		gameObjects.pop_back();
		delete back;
	}
	
	return 0;
}