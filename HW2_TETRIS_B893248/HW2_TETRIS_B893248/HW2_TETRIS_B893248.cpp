#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <vector>
#include <string>
#include "Utils.h"

using namespace std;

class GameObject {
	char*		shape;
	int			width;
	int			height;
	Position	pos;
	Screen&		screen;
	bool		activation;

	vector <GameObject*> children;

public:
	GameObject(const char* shape, int width, int height, const Position& pos = Position{ 1,0 })
		: height(height), width(width), shape(nullptr), pos(1, 0), activation(false),
		screen(Screen::getInstance()) {
		if (!shape || strlen(shape) == 0 || width == 0 || height == 0)
		{
			this->shape = new char[1];
			this->shape[0] = 'x';
			width = 1;
			height = 1;
		}
		else {
			this->shape = new char[width*height];
			strncpy(this->shape, shape, width*height);
		}
		this->width = width;
		this->height = height;
	}

	virtual ~GameObject() {
		if (shape) { delete[] shape; }
		width = 0, height = 0;
	}

	bool isActive() { return activation; }
	void setActivation(bool setting) { activation = setting; }

	void addChild(GameObject* child) {
		if (!child) return;
		children.push_back(child);
	}
	
	void setShape(const char* shape) {
		if (!shape) return;
		strncpy(this->shape, shape, width*height);
	}

	void setPos(int x, int y) { this->pos.x = x; this->pos.y = y; }

	Position& getPos() { return pos; }

	virtual void draw() {
		screen.draw(shape, width, height, pos);
	}

	virtual void update() {}
};

// 테트리스 게임의 영역(맵)과 다음 블록을 보여주고, 배치된 블록을 관리하는 클래스
class Board : public GameObject {
	int width;
	int height;
	int size;
	char* boardMap;
	Screen& screen;
	Position pos;

	//bool		isPlaying;
	int count;

	static Board* instance;
	Board()
		: width(12), height(21), size(width*height), count(0),
		boardMap(new char[size]), screen(Screen::getInstance()),
		GameObject(boardMap, width, height, Position{ 0,0 })
	{
		GameObject::setActivation(true); //활성화
		initBoard(); //초기화
		Borland::gotoxy(0, 0);
		draw();
	}
public:
	static Board& getInstance() {
		if (instance == nullptr) instance = new Board();
		return *instance;
	}

	//보드 초기화 : 벽, 빈칸, 바닥을 그려줍니다
	void initBoard() {
		int i;
		for (i = 0; i < (size - width); i++) {
			if (i % 12 == 0 || i % 12 == 11)	boardMap[i] = 'l'; //벽
			else								boardMap[i] = ' '; //빈칸
		}
		for (i; i < size; i++)					boardMap[i] = '-'; // 바닥
	}

	//해당 좌표에 블록의 유무를 기록합니다
	void setBlock(int x, int y, const char* shape, int w, int h) { 
		int idx = x + (y * this->width);
		for (int i = 0; i < h; i++) {
			if (i>0) idx += this->width;
			for (int j = 0; j < w; j++) {
				if (shape[j+i*w] == ' ')	continue;
				boardMap[idx +  j] = shape[j + i * w];
			}
		}
	}

	char getBoard(int x, int y) {
		return boardMap[x + (y*width)];
	}
	
	void draw() {
		screen.draw(boardMap, width, height, pos);
	}

	bool checkLines() { 
		count = 0;
		for (int i = 1; i < width*(height - 1); i++) {			
			if (i % 12 == 0) continue;
			else if (i % 12 == 11) {
				count = 0; //카운트 초기화
				continue;
			} //벽은 카운트하지 않습니다

			if (boardMap[i] != ' ') count++; //블록을 카운트 합니다
			if (count == 10) { //한 라인이 다 찼을 경우
				for (int j = i-width; j > 0; j--)
					boardMap[j+width] = boardMap[j]; //위의 블록들을 모두 한 칸 아래로 내립니다
				count = 0;
			} 
		} count = 0;
		return true;
	}

	void update() {
		checkLines();
		//if (!isPlaying) {
		//	cout << "GAMEOVER ! ";
		//	Sleep(500);
		//	exit(-1);
		//}
	}
};
Board* Board::instance = nullptr;


class Block : public GameObject {
	vector<string>	sprites;
	int				width;
	int				height;
	int				current;
	char*			shape;

public:
	Block(vector<string>& sprites, int w, int h, const Position& pos = Position{ 1,0 })
		: sprites(sprites), width(w), height(h), current(0),
		GameObject(sprites[current].c_str(), w, h, pos) {}
	
	~Block() { delete[] shape; }

	bool isCollided(const char* shape, int w, int h) {
		int xPos = getPos().x, yPos = getPos().y, initX = xPos;

		for (int i = 0; i < w*h; i++) {
			if (i>0 && i%w == 0) { xPos = initX, yPos++; }; // shape에서 다음 줄이면 xPos값 초기화
			
			if (shape[i] == ' ') { xPos++; continue; }
			if (i+w<w*h && shape[i + w] != ' ') { xPos++; continue; } //shape에서 마지막 블록라인이 아닌데 그 밑이 블록인경우

			if (Board::getInstance().getBoard(xPos, ++yPos) != ' ') { return true; }
			--yPos;
		}
		return false;
	}

	void update() {
		WORD keyCode;

		if (Input::GetKeyEvent(keyCode)) {
			switch (keyCode) {
			case VK_RIGHT:
				if (getPos().x + this->width == 11) //x좌표 값이 맵의 좌표보다 크게 될 경우 이동제한
					break;
				else getPos().x++;
				break;

			case VK_LEFT:
				if (getPos().x == 1) //x좌표 값이 맵의 좌표보다 작게 될 경우 이동제한
					break;
				else getPos().x--;
				break;

			case VK_UP:
				current = (current + 1) % sprites.size();
				setShape(sprites[current].c_str());
				break;

			case VK_DOWN:
				if (Board::getInstance().getBoard(getPos().x, getPos().y + this->height + 1) == ' ')
					getPos().y++;
				break;

			case 0x41: //'a'
				current = (current + 1) % sprites.size();
				setShape(sprites[current].c_str());
				break;

			case 0x44: //'d'
				current = (current + 3) % sprites.size();
				setShape(sprites[current].c_str());
				break;
			}
		}

		//바닥이나 다른 블록과의 충돌여부를 체크합니다
		if (isCollided(sprites[current].c_str(), this->width, this->height)) { 
			shape = new(char[this->width*this->height]);
			strcpy(shape, sprites[current].c_str());
			Board::getInstance().setBlock(getPos().x, getPos().y, shape, this->width, this->height);
			GameObject::setActivation(false);
		}
		
		else
			getPos().y = (getPos().y + 1) % Screen::getInstance().getHeight();
	}
};

int main()
{
	Screen&	 screen = Screen::getInstance();
	vector<GameObject *> blocks;
	Board&	board = Board::getInstance();

	system("mode con cols=45 lines=60");
	system("chcp 437");

	vector<string> Blk1 = {
		{" xxxxxxxxx"}
	};
	vector<string> Blk2 = {
		{"zzzz"}
	};
	vector<string> L_Block = {
		{"x  x  xx "}, {"   xxxx  "}, {"xx  x  x"}, {"     xxxx"}
	};
	vector<string> J_Block = {
		{"  x  x xx"}, {"   x  xxx"}, {"xx x  x  "}, {"   xxx  x"}
	};
	vector<string> O_Block = {
		{"xxxx"}
	};
	//vector<string> S_Block = {
	//	{" xx x xx "}, {"x  xxx  x"}
	//};
	//vector<string> Z_Block = {
	//	{"xx  x  xx"}, {"  xxxxx  "}
	//};
	//vector<string> T_Block = {
	//	{"   xxx x "}, {"  x xx  x"}, {"    x xxx"}, {"   x  xx x  "}
	//};
	//vector<string> I_Block = {
	//	{"x   x   x   x   "}, {"         xxxx"}
	//};


	blocks.push_back(new Block(Blk1, 10, 1, Position{ 1,0 })); //for debuging
	blocks.push_back(new Block(Blk2, 1, 4, Position{ 1,0 }));  //for debuging
	blocks.push_back(new Block(L_Block, 3, 3, Position{ 3,0 }));
	blocks.push_back(new Block(O_Block, 2, 2, Position{ 3,0 }));
	blocks.push_back(new Block(J_Block, 3, 3, Position{ 3,0 }));
	//blocks.push_back(new Block(S_Block, 3, 3, Position{ 3,0 }));
	//blocks.push_back(new Block(Z_Block, 3, 3, Position{ 3,0 }));
	//blocks.push_back(new Block(T_Block, 3, 3, Position{ 3,0 }));
	//blocks.push_back(new Block(I_Block, 4, 4, Position{ 3,0 }));

	blocks[0]->setActivation(true);

	screen.clear(); screen.render();

	int count = 0;
	int idx = 1;
	int size = 5;
	while (true)
	{
		screen.clear();
		board.draw();
		for (int i= size-1; i>-1; i-- ) {
			if (blocks[i]->isActive())
				blocks[i]->update();
			else
				count++;
		}
		board.update();
		
		//이전 블록이 비활성화 되었다면 다음 블록을 활성화 합니다.
		if (count == size) {
			if (idx == size) idx = 0;
			blocks[idx]->setActivation(true);
			blocks[idx]->setPos(1,0);
			idx++;
		}
		count = 0;

		screen.clear();
		board.draw();
		for (int i = size - 1; i > -1; i--) {
			if (blocks[i]->isActive())	blocks[i]->draw();
		}

		Sleep(200);
		screen.render();
		board.draw();

		Input::EndOfFrame();
	}

	return 0;
}