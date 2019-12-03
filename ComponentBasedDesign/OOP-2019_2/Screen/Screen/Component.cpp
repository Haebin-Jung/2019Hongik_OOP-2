#include "Component.h"
#include "GameObject.h"


Component::Component(GameObject* gameObject)
	: gameObject(gameObject),
	transform(gameObject->getTransform())
{
	if (transform == nullptr) {
		transform = gameObject->getTransform();
		//생성시에 호출이 안됐다면 다시 설정
	}
}


Component::~Component()
{
}
