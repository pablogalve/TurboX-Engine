#include "Component_Light.h"

C_Light::C_Light(Component::Type type, GameObject* owner) : Component(type, owner)
{	
	this->owner = owner;
}

C_Light::~C_Light()
{
}
