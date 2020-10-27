#include "Component_Material.h"

C_Material::C_Material(Component::Type type, GameObject* owner):Component(type, owner)
{
	this->owner = owner;
}

C_Material::~C_Material()
{
}

Component::Type C_Material::GetComponentType()
{
	return Component::Type::Material;
}
