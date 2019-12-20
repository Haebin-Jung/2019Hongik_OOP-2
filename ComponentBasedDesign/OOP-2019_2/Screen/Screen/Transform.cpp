#include "Component.h"
#include "Transform.h"
#include <string>


Transform::Transform(GameObject* gameObject,
	const string& shape,
	const Vector2& position,
	const Vector2& rotation,
	const Vector2& scale)
	: shape(shape),
	position(position), 
	rotation(rotation), 
	scale(scale),
	Component(gameObject),
	screen(Screen::getInstance())
{
}

Transform::~Transform()
{
}

void Transform::start() {}

void Transform::update() 
{
	if (shape == "") return;
	screen.draw(shape.c_str(), shape.size(), 1, position); // 높이 정보는 추후에 수정 필요
}