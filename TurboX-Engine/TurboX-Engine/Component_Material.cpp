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
	data->AddUInt("UUID", component_UUID);
	data->AddUInt("Owner UUID", owner->GetUUID());

	if (resourceTexture != nullptr) {
		data->AddString("Texture Name", resourceTexture->GetName());
	}

	if (colors.IsZero() == false) {
		data->AddVector3("Colors", colors);
	}
	
	return ret;
}

bool C_Material::Load(Config* data)
{
	bool ret = true;
	
	component_UUID = data->GetUInt("UUID");
	colors = data->GetVector3("Colors", { 0,0,0 });

	string texture_name = data->GetString("Texture Name", "Unnamed");

	if (texture_name != "Unnamed") {
		resourceTexture = (ResourceTexture*)App->resources->Get(App->resources->FindByName(texture_name.c_str(), Resource::ResType::Texture));
		resourceTexture->LoadInMemory();
	}

	C_Mesh* owner_mesh = nullptr;
	if (owner_mesh = (C_Mesh*)owner->GetComponent(Component::Type::Mesh)) {
		owner_mesh->SetMaterial(this);
	}

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