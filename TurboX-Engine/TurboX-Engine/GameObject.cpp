#include "GameObject.h"

GameObject::GameObject()
{
	active = true;
	name = "";
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
}

Component* GameObject::CreateComponent(Component::Type type)
{
	return nullptr;
}
