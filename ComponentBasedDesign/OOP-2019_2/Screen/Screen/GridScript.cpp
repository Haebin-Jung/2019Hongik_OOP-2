#include "GridScript.h"



GridScript::GridScript(GameObject* gameObject)
	: width(0), height(0), Component(gameObject)
{

}


GridScript::~GridScript()
{
}

void GridScript::start() {
	this->width = 10;
	this->height = 10;
}