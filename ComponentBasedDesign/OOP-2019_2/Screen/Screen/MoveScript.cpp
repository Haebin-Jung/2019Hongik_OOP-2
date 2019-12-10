#include "GameObject.h"
#include "MoveScript.h"
#include "Utils.h"

using namespace std;

MoveScript::MoveScript(GameObject* gameObject)
	: Component(gameObject)
{

}


MoveScript::~MoveScript()
{
}

void MoveScript::start()
{
	Borland::gotoxy(0, 0);
}

void MoveScript::update()
{
	Borland::gotoxy(0, 1);
}
