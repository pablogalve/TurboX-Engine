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
	material_path = (std::string)file_name;
	ilGenImages(1, &ImageName);
	ilBindImage(ImageName);
	ilLoadImage(file_name);
	TextureID = ilutGLBindTexImage();
	ilDeleteImages(1, &ImageName);
}

void C_Material::UnLoadTexture()
{
	glBindBuffer(GL_TEXTURE_2D, 0);
}

Component::Type C_Material::GetComponentType()
{
	return Component::Type::Material;
}
