#include "Component.h"

Component::Component(Type type, GameObject* owner)
{
	active = true;
	this->owner = owner;
}

Component::~Component()
{
}

void Component::Enable()
{
}

void Component::Update()
{
}

void Component::Disable()
{
}
