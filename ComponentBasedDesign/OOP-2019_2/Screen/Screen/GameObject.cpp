#include "GameObject.h"
#include "Transform.h"
#include <algorithm>

/* STATIC VARIABLES and FUNCTIONS*/
vector<GameObject*> GameObject::gameObjects;

GameObject* GameObject::Find(const string& path) {
	for (auto obj : gameObjects)
	{
		if (obj->getName() == path) return obj;
	}
	return nullptr;
}

void GameObject::Add(GameObject* obj) {
	if (obj == nullptr) return;
	gameObjects.push_back(obj);
}

void GameObject::Remove(GameObject* obj) {
	//using iterator
	if (obj == nullptr) return;

	//for each�� eraseó�� ��ȭ�� ���� ��쿡�� ���Ұ�
	for (auto it = gameObjects.begin(); it != gameObjects.end(); ) {
		auto o = *it;
		if (o == obj) {
			it = gameObjects.erase(it); //���� ���� ���·� update
			delete o;
		}
		else { it++; }
	}

	////erase-remove idiom //������� ����
	//gameObjects.erase(std::remove_if(
	//	gameObjects.begin(),	//ó������
	//	gameObjects.end(),		//������
	//	[&](GameObject* item) { return obj == item; } //Ư�� ������ true�� �Ǵ� ��Ȳ�� ���Ͽ� ����function?
	//	// []��� �����Ұ��� = copy by value/ & call by reference, �������� ������ ��� ', ���� ������'���� ����
	//	// {}������ �����ϴ� �Ϳ� ���Ͽ� �����Ѵ�. ���� for�������� if���� �ش��ϴ� ����.
	//), gameObjects.end()); //end�� ������ element ������ ���� �ǹ��Ѵ�.
}

/* General variables and functions */

GameObject::GameObject(const string& name, 
	GameObject* parent, const string& tag, 
	const string& shape, const Vector2& pos)
	: name(name), tag(tag), enabled(true), parent(parent),
	transform(new Transform(this, shape, pos) ) {
	components.clear();
	components.push_back(transform);
}

GameObject::~GameObject() {}

void GameObject::traverseStart() {
	if (enabled == false) return;

	for (auto comp : components)
	{
		comp->start();
	}
	for (auto child : children)
	{
		child->traverseStart();
	}
}

void GameObject::traverseUpdate() {
	if (enabled == false) return;

	for (auto comp : components)
	{
		comp->update();
	}
	for (auto child : children)
	{
		child->traverseUpdate();
	}
}