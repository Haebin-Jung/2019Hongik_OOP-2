#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Utils.h"
using namespace std;


enum ScreenState{
	Close = 1,
	Open = 2,
	Flag = 3
};

enum MinesMapState {
	Empty = 1,	//빈 땅
	Mine = 2	//지뢰매설지
};

class MineSweeperMap {
	int w;			//맵의 가로길이
	int h;			//맵의 세로길이
	int mines;		//지뢰 개수
	int size;
	int isPlaying;
	char *screen;	//플레이어에게 보여지는 화면
	char *minesMap;	//매설지뢰의 위치

	Position buttonPos[81];
	Position mousePos;
	
public:
	MineSweeperMap(int width = 9, int height = 9) : w(width), h(height), mines(10), size(w*h), screen(new char[w*h+1]), minesMap(new char[w*h+1]) //defalt 9*9
	{
		Borland::initialize();
		memset(screen, Close, size+1); //스크린 상태 : 모두 닫힘
		screen[size + 1] = '\0';
	}

	virtual ~MineSweeperMap() {
		delete[] minesMap;
		delete[] screen;
	}

	//게임 시작 함수
	void startGame()
	{
		isPlaying =1;
		layMines(mines); //지뢰깔기
		do {
			draw();
		} while (isPlaying != 0);
	}

	void checkPlaying() { //교재 241쪽 102번라인 게임종료검사함수 참조했습니다
		int cnt = 0;
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				if (screen[j + i * w] != Open) //마크해둬서 열리지 않은 칸이면 발견한 지뢰의 수 카운트
					cnt++;
				else if (screen[j + i * w] == Open && minesMap[j + i * w] == Mine) {
					Borland::gotoxy(buttonPos[w / 3].x, buttonPos[h + 2].y);
					printf("B A N G !\nYOU LOSE !");
					return;
				}
			}
		}
		if (cnt == mines) { //다 찾음
			Borland::gotoxy(buttonPos[0].x, h+2);
			printf("CONGRATULATIONS ! ! !\nYOU WIN !");
			return;
		}
		else //아직 하는 중
			return;
	}
	
	//지뢰 매설 함수
	void layMines(int mines = 10)	
	{
		memset(minesMap, Empty, size + 1); //지뢰밭 상태 : 지뢰 없음
		minesMap[size + 1] = '\0';

		int idx, m = mines;
		srand((unsigned int)time(NULL));

		do {
			idx = rand() % size;
			if (minesMap[idx] == (char)Mine);
			else {
				minesMap[idx] = (char)Mine;
				m--;
			}
		} while (m > 0);

		return;
	}

	int getIndex(int x, int y) {
		if (x < 0 || y < 0 || x > buttonPos[size - 1].x || y > buttonPos[size - 1].y) //비정상입력
			return -1;

		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				if (x == buttonPos[j + (i*w)].x && y == buttonPos[j + (i*w)].y)
					return buttonPos[j + (i*w)].index;
			}
		}
		return -1;
	}

	//땅파기 함수
	void dig(short x, short y) {
		if (x < buttonPos[0].x || x > buttonPos[size - 1].x || y < buttonPos[0].y || y > buttonPos[size - 1].y)
			return;

		int idx = getIndex(x, y);
		if (idx == -1)
			return;
		if (screen[idx] == (char)Open) //이미 열린 칸은 반환
			return;
			
		int count;
		short tmpX, tmpY;
		if (minesMap[idx] == (char)Empty) { //지뢰가 아니면 실행
			screen[idx] = (char)Open; //칸 열어주기
			count = countNumOfMines(x, y); //주변탐색
			if (count != 0)
				return;
			else {
				dig(x - 2, y - 1);
				dig(x, y - 1);
				dig(x + 2, y - 1);
				dig(x - 2, y);
				dig(x + 2, y);
				dig(x - 2, y + 1);
				dig(x, y + 1);
				dig(x + 2, y + 1);
			}
		}

		return;
	}

	//주변 지뢰개수 함수
	int countNumOfMines(int posX, int posY) {
		int idx, x, y, cntMines = 0;
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				x = posX + j * 2;
				y = posY + i;
				idx = getIndex(x, y);
				if (idx < 0 || idx > size)
					continue;
				if (minesMap[idx] == Mine)
					cntMines++;
			}
		}

		return cntMines;
	}

	//화면그림 함수
	void draw() {
		clear();
		Borland::gotoxy(buttonPos[0].x, buttonPos[0].y);
		int count = 0;
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				buttonPos[count].x = Borland::wherex();
				buttonPos[count].y = Borland::wherey();
				buttonPos[count].index = count;

				if (screen[j + (w*i)] == Close) printf("■");	//닫힌 곳
				else if (screen[j + (w*i)] == Flag) printf("＃");	//깃발표시

				else if (screen[j + (w*i)] == Open) {
					if (minesMap[j + (w*i)] == Empty) printf("%2d", countNumOfMines(buttonPos[count].x, buttonPos[count].y));
					else if (minesMap[j + (w*i)] == Mine) printf("※");
				}
				count++;
			}
			printf("\n");
		}
		Borland::gotoxy(buttonPos[0].x, buttonPos[w*h + 1].y);
		printf("발견한 지뢰:%2d // 심어진 지뢰:%2d\n", getNumOfFlags(), mines);

		Sleep(30);
		if (isPlaying)	getMouseButtonDown();
		else return;
	}

	int getNumOfFlags() {
		int cnt = 0;
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				if (screen[j + i * w] == Flag) //마크해둬서 열리지 않은 칸이면 발견한 지뢰의 수 카운트
					cnt++;
			}
		}
		return cnt;
	}

	void getMouseButtonDown() {
		INPUT_RECORD ir;
		DWORD ic;
		SetConsoleMode(hin, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
		while (1) {
			checkPlaying();
			pos.X = -1;
			pos.Y = -1;
			ReadConsoleInput(hin, &ir, 1, &ic);
			if (ir.EventType == MOUSE_EVENT) {
				if (ir.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
					pos.X = ir.Event.MouseEvent.dwMousePosition.X;
					pos.Y = ir.Event.MouseEvent.dwMousePosition.Y;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

					if (pos.X < buttonPos[0].x || pos.X > buttonPos[size - 1].x || pos.Y < buttonPos[0].y || pos.Y>buttonPos[size - 1].y)
						return; // 입력 범위 벗어남

					mousePos.x = pos.X;
					mousePos.y = pos.Y;

					int tmp = mousePos.x % 2;
					if (tmp == 1) mousePos.x--; //좌표조정

					dig(mousePos.x, mousePos.y);
					draw();
				}
				else if (ir.Event.MouseEvent.dwButtonState & RIGHTMOST_BUTTON_PRESSED) { // 우클릭
					pos.X = ir.Event.MouseEvent.dwMousePosition.X;
					pos.Y = ir.Event.MouseEvent.dwMousePosition.Y;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

					if (pos.X < buttonPos[0].x || pos.X > buttonPos[size - 1].x || pos.Y < buttonPos[0].y || pos.Y>buttonPos[size - 1].y)
						return; // 입력 범위 벗어남
					mousePos.x = pos.X;
					mousePos.y = pos.Y;

					int tmp = mousePos.x % 2;
					if (tmp == 1) mousePos.x--; //좌표조정

					mark(mousePos.x, mousePos.y);
					draw();
				}
			}

		}
	}

	void mark(short x, short y) {
		int idx = getIndex(x, y);
		if (idx < 0 || idx > size)
			return;

		if (screen[idx] == Close)
			screen[idx] = Flag;
		else
			screen[idx] = Close; //표시 취소
	}

	void clear() {
		COORD Coor = { 0, 0 };
		DWORD dw;
		FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', 80 * 25, Coor, &dw);
	}
};

int main()
{
	MineSweeperMap minesweeper(9, 9);
	minesweeper.startGame();

	return 0;
}
