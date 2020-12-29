#include "Component_Billboard.h"

C_Billboard::C_Billboard(Component::Type type, GameObject* owner) : Component(type, owner)
{
	this->owner = owner;
}

C_Billboard::~C_Billboard()
{
}
