#include "GameObject.h"
#include "Application.h"
#include "ModuleScene.h"

GameObject::GameObject()
{	
	active = true;
	ChangeName("Custom Mesh");
	is_selected = false;
}

GameObject::~GameObject()
{
	mesh = nullptr;
	delete mesh;
}

void GameObject::Update()
{
}

Component* GameObject::CreateComponent(Component::Type type)
{
	Component* new_component = nullptr;

	switch (type)
	{
	case Component::Type::None:		
		break;
	case Component::Type::Transform:
		new_component = new C_Transform(Component::Type::Transform, this);
		break;
	case Component::Type::Mesh:
		//new_component = new C_Mesh(Component::Type::Mesh, this);
		mesh = new C_Mesh(Component::Type::Mesh, this);		
		break;
	case Component::Type::Material:
		new_component = new C_Material(Component::Type::Material, this);
		break;
	case Component::Type::Light:
		new_component = new C_Light(Component::Type::Light, this);
		break;
	default:
		break;
	}

	if(new_component)
		components.push_back(new_component);

	return new_component;
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

bool GameObject::Get_IsSelected()
{
	return is_selected;
}

void GameObject::Select()
{
	is_selected = true;
}

void GameObject::Unselect()
{
	is_selected = false;
}
