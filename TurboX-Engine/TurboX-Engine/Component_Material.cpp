#include "Component_Material.h"

C_Material::C_Material(Component::Type type, GameObject* owner):Component(type, owner)
{
	this->owner = owner;
}

C_Material::~C_Material()
{
}

void C_Material::LoadTexture(const char* file_name)
{
	ilGenImages(1, &ImageName);
	ilBindImage(ImageName);
	ilLoadImage(file_name);
	TextureID = ilutGLBindTexImage();
	ilDeleteImages(1, &ImageName);
}

Component::Type C_Material::GetComponentType()
{
	return Component::Type::Material;
}
