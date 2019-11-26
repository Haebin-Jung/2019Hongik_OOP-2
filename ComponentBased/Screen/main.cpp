// 2019 홍익대학교 2학년 2학기 객체지향프로그래밍(2) 수업
// 2019 Honik Univ. OOP(2) class
// Component-based Design
#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <array>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include "GameObject.h"
#include "GameEngine.h"
#include "Component.h"
#include "Transform.h"

using namespace std;


int main()
{
	GameEngine& engine = GameEngine::getInstance();

	engine.mainLoop();	

	return 0;
}