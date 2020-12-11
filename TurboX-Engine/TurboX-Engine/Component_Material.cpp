#include "Application.h"
#include "ModuleFileSystem.h"
#include "Component_Material.h"
#include "ModuleInput.h"
#include "GameObject.h"
#include "ModuleResources.h"

C_Material::C_Material(Component::Type type, GameObject* owner):Component(type, owner)
{
	
}

C_Material::~C_Material()
{
}

bool C_Material::Save(Config* data)
{
	bool ret = true;

	
	return ret;
}

Component::Type C_Material::GetComponentType()
{
	return Component::Type::Material;
}

const bool C_Material::HasTexture() const
{
	bool ret;
	resourceTexture ? ret = true : ret = false;
	return ret;
}

void C_Material::SetResource(uint resource)
{
	resourceTexture = (ResourceTexture*)App->resources->Get(resource);
	resourceTexture->LoadInMemory();
	component_UUID = resource;
}

const uint C_Material::GetTexID() const
{
	if (HasTexture()) {
		return resourceTexture->gpuID;
	}
	return -1;
}