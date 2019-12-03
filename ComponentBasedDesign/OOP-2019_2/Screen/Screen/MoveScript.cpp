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
	cout << gameObject->getName() << " start func called" << endl;
}

void MoveScript::update()
{
	Borland::gotoxy(0, 1);
	cout << gameObject->getName() << " update func called";
}
