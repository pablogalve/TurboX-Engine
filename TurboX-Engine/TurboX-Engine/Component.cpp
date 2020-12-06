#include "Component.h"
#include "GameObject.h"

Component::Component(Type type, GameObject* owner)
{
	active = true;
	this->owner = owner;

	component_UUID = owner->GenerateUUID();	
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

Component::Type Component::GetComponentType()
{
	return Component::Type::None;
}

bool Component::Save(Config* data)
{
	bool ret = true;

	return ret;
}