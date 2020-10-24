#include "Component.h"

Component::Component(Type type)
{
	active = true;
	owner = nullptr;
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
