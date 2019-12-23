#include "GameObject.h"
#include "MoveScript.h"
#include "Transform.h"
#include "Utils.h"
#include "BlockScript.h"

using namespace std;

MoveScript::MoveScript(GameObject* gameObject)
	: Component(gameObject), gm(nullptr), bs(nullptr)
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
	bs = static_cast<BlockScript*> (gameObject->getComponent<BlockScript>());
	return;
}

void MoveScript::update()
{
	if (bs == nullptr || !bs->movable)
		return;
	Vector2 pos = transform->getPosition();
	dropBlock(pos);
	move(pos);
	
	gm->resideInside(pos, bs->width, bs->height);
	transform->setPosition(pos);
}

void MoveScript::dropBlock(Vector2& pos) {
	
	if (pos.Y() + bs->getBlockHeight() == gm->getBottom())
	{
		bs->collision = true;
		bs->movable = false;
	}
	else { pos += Vector2{ 0, 1 }; }
	return;
}

void MoveScript::move(Vector2& pos) {	
	if (!bs->movable) return ;

	// 블록 이동 및 로테이션 입력
	if (Input::GetKeyDown(KeyCode::Left)) {  pos += Vector2{ -1,0 }; }
	if (Input::GetKeyDown(KeyCode::Right)) { pos += Vector2{ 1,0 }; }
	if (Input::GetKeyDown(KeyCode::Down)) { dropBlock(pos); };
	if (Input::GetKeyDown(KeyCode::Up)) { 
		bs->rotation = (bs->rotation+1)%4;
		bs->rotateBlock(bs->blockNum, bs->rotation); 
	}
	return;
}