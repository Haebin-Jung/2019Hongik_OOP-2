#pragma once

#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;

struct Vector2 {
	float x;
	float y;
	const int X() const { return (int)x; }
	const int Y() const { return (int)y; }
	Vector2(float x = 0, float y = 0) : x(x), y(y) {}
	Vector2(const Vector2& other) : Vector2(other.x, other.y) {}

	static Vector2 zero;
	static Vector2 ones;
	static Vector2 up;
	static Vector2 down;
	static Vector2 left;
	static Vector2 right;

	double magnitude() {
		return sqrt(this->sqrMagnitude());
	}

	double sqrMagnitude() {
		return (double)x * x + y * y;
	}

	Vector2 operator-(const Vector2& other) {
		return Vector2{ this->x - other.x, this->y - other.y };
	}

	static friend Vector2 operator-(Vector2& a, const Vector2& b);

	static friend double Distance(Vector2& a, const Vector2& b);
	
	
	Vector2 operator+(const Vector2& other) {
		return Vector2{ this->x + other.x, this->y + other.y };
	}
	bool operator==(const Vector2& other) {
		return (x == other.x && y == other.y);
	}

	Vector2& operator+=(const Vector2& other) {
		x += other.x, y += other.y;
		return *this;
	}
};


enum class KeyCode {
	Space = 0,
	Left,
	Right,
	Up,
	Down,

	Esc,
	Enter,

	A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z
};


class Input {
	static INPUT_RECORD InputRecord[128];
	static DWORD Events;
	static bool evaluated;
	static bool gotMouseEvent;
	static bool gotKeyEvent;
	static Vector2 mousePosition;
	static WORD vKeyCode;	

public:
	static void GetEvent();

	static void EndOfFrame();

	static void Initialize();
	static bool GetMouseEvent(Vector2& pos);

	static bool GetKeyEvent(WORD& keyCode);

	static bool GetKeyDown(KeyCode key);
};


class Borland {

public:
	

	static int wherex()
	{
		CONSOLE_SCREEN_BUFFER_INFO  csbiInfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
		return csbiInfo.dwCursorPosition.X;
	}
	static int wherey()
	{
		CONSOLE_SCREEN_BUFFER_INFO  csbiInfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
		return csbiInfo.dwCursorPosition.Y;
	}
	static void gotoxy(int x, int y)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), _COORD{ (SHORT)x, (SHORT)y });
	}
	static void gotoxy(const Vector2* pos)
	{
		if (!pos) return;
		gotoxy( (*pos).X(), (*pos).Y());
	}
	static void gotoxy(const Vector2& pos)
	{
		gotoxy( pos.X(), pos.Y());
	}
};

class Screen {
	int width;
	int height;
	char* canvas;

	static Screen* instance;
	Screen(int width = 90, int height = 50)
		: width(width), height(height),
		canvas(new char[(width + 1)*height])

	{
		Input::Initialize();
	}
public:
	static Screen& getInstance() {
		if (instance == nullptr) {
			instance = new Screen();
		}
		return *instance;
	}

	~Screen() {
		if (instance) {
			delete[] canvas;
			instance = nullptr;
		}
	}

	int getWidth() const { return width; }

	int getHeight() const { return height;  }

	void drawRect(const Vector2& pos, int w, int h)
	{
		canvas[pos.X()] = '\xDA';
		canvas[pos.X() + w-1] = '\xBF';
		memset(&canvas[pos.X() + 1], '\xC4', w - 2);
		canvas[pos.X() + (pos.Y() + (h - 1))*(width + 1)] = '\xC0';
		canvas[pos.X() + (pos.Y() + (h - 1))*(width + 1) + w-1] = '\xD9';
		memset(&canvas[pos.X() + 1 + (pos.Y() + (h - 1))*(width + 1)], '\xC4', w - 2);
		for (int i = 1; i < h-1; i++) {
			canvas[pos.X() + (pos.Y() + i)*(width + 1)] = '\xB3';
			canvas[pos.X() + w-1 + (pos.Y() + i)*(width + 1)] = '\xB3';
		}
	}

	void draw(const char* shape, int w, int h, const Vector2& pos)
	{
		if (!shape) return;
		for (int i = 0; i < h; i++)
		{
			strncpy(&canvas[pos.X() + (pos.Y() + i)*(width + 1)], &shape[i*w], w);
		}
	}

	void render()
	{
		for (int i = 0; i < height; i++)
			canvas[width + i * (width + 1)] = '\n';
		canvas[width + (height - 1) * (width + 1)] = '\0';
		Borland::gotoxy(0, 0);
		cout << canvas;
	}

	void clear()
	{
		memset(canvas, ' ', (width + 1)*height);
		canvas[width + (height - 1)*(width + 1)] = '\0';
	}
};