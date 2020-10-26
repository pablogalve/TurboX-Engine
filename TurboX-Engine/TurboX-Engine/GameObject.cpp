#include "GameObject.h"

GameObject::GameObject()
{	
	active = true;
	name = "";

	//mesh = new C_Mesh(Component::Type::Mesh);
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

void GameObject::Draw()
{
	mesh->Draw();

	for (size_t i = 0; i < childs.size(); i++)
	{
		if (childs[i]->active)
			childs[i]->Draw();
	}
}

void GameObject::ChangeName(std::string _name)
{
	name = _name;
}
