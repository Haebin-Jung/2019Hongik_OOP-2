#include "Component.h"



Component::Component(GameObject* gameObject)
	: gameObject(gameObject), transform(gameObject->getTransform())
{}

Component::~Component() {}

void Component::awake() {}
void Component::onEnable() {}
void Component::start() {}
void Component::fixedUpdate() {}
void Component::update() {}
void Component::lateUpdate() {}
void Component::onDisable() {}
void Component::onDeestroy() {}

void Component::doUpdate(Component* comp) { comp->update(); };
