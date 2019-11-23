// 2019 홍익대학교 2학년 2학기 객체지향프로그래밍(2) 수업
// 2019 Honik Univ. OOP(2) class
// Component-based Design
#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <array>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include "Utils.h"
#include "Component.h"
#include "GameObject.h"
#include "Transform.h"
#include "GameEngine.h"

using namespace std;


int main()
{
	GameEngine& engine = GameEngine::getInstance();

	engine.mainLoop();	

	return 0;
}