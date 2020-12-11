#include "Component.h"
#include "GameObject.h"
#include "Application.h"
#include "ModuleResources.h"

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

bool Component::Load(Config* data)
{
	return true;
}

Resource* Component::GetResource() const
{
	return App->resources->Get(component_UUID);
}