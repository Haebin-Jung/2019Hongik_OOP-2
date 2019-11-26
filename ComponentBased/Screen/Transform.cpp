#pragma once
#include "Transform.h"

//참조할 클래스 포함
#include "GameObject.h"


Transform::Transform(GameObject* gameObject,
	const Vector2& position = Vector2::zero,
	const Vector2& rotation = Vector2::zero,
	const Vector2& scale = Vector2::one)
	: position(position), rotation(rotation), scale(scale),
	Component(gameObject)
{}

void Transform::start() {}
void Transform::update() {}