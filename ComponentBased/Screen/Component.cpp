#include "Component.h"



Component::Component()
{
}


Component::~Component()
{
}


Component::Component(GameObject* gameObject)
		: gameObject(gameObject),
		transform(gameObject->getTransform())
	{}

Component::~Component() {}
	
GameObject* gameObject;
void awake() {}
void onEnable() {}
void start() {}
void fixedUpdate() {}
void update() {}
void lateUpdate() {}
void onDisable() {}
void onDeestroy() {}
