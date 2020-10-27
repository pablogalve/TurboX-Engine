#include "GameObject.h"
#include "Application.h"
#include "ModuleScene.h"

GameObject::GameObject()
{	
	active = true;
	ChangeName("GameObjectTest");

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
	parent = App->scene->GetRoot();
	switch (type)
	{
	case Component::Type::None:		
		break;
	case Component::Type::Transform:
		//new_component = new C_Transform();
		break;
	case Component::Type::Mesh:
		//new_component = new C_Mesh(Component::Type::Mesh, this);
		mesh = new C_Mesh(Component::Type::Mesh, this);		
		break;
	case Component::Type::Material:
		//new_component = new C_Material();
		break;
	case Component::Type::Light:
		//new_component = new C_Material();
		break;
	default:
		break;
	}

	components.push_back(new_component);

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
