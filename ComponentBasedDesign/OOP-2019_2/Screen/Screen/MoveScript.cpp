#include "GameObject.h"
#include "MoveScript.h"
#include "Transform.h"
#include "Utils.h"

using namespace std;

MoveScript::MoveScript(GameObject* gameObject)
	: Component(gameObject), gm(nullptr)
{

}


MoveScript::~MoveScript()
{
}

void MoveScript::start()
{
	auto map = GameObject::Find("map");
	if (map == nullptr) return;
	gm = static_cast<GridManager *> (map->getComponent<GridManager>());
}

void MoveScript::update()
{
	Vector2 pos = transform->getPosition();
	int direction = rand() % 5;
	switch (direction)
	{
	case 0:	break;
	case 1: pos += Vector2{ 1,0 };	break;
	case 2:	pos += Vector2{ -1,0 }; break;
	case 3:	pos += Vector2{ 0,1 }; 	break;
	case 4: pos += Vector2{ 0,-1 };	break;
	}
	gm->resideInside(pos);
	transform->setPosition(pos);
}
