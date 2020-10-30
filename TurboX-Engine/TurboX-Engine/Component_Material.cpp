#include "Application.h"
#include "ModuleFileSystem.h"
#include "Component_Material.h"

C_Material::C_Material(Component::Type type, GameObject* owner):Component(type, owner)
{
	this->owner = owner;
	imageName = 0;
	checkersImage = 0;
	defaultTex = false;
	material_path = "";
	LoadDefaultTex();
}

C_Material::~C_Material()
{
}

void C_Material::LoadTexture(const char* file_name)
{	
	material_path = (std::string)file_name;

	char* buffer = nullptr;
	std::string full_path = "Assets/";
	full_path.append(file_name);

	uint size = App->file_system->Load(full_path.c_str(), &buffer);

	ilGenImages(1, &imageName);
	ilBindImage(imageName);

	if (ilLoadL(IL_TYPE_UNKNOWN, (const void*)buffer, size))
	{
		textureID = ilutGLBindTexImage();
		ilDeleteImages(1, &imageName);
	}
	
	RELEASE_ARRAY(buffer);
}

void C_Material::UnLoadTexture()
{
	if (textureID != 0)
	{
		glDeleteTextures(1, &textureID);
		textureID = 0;
	}
}
	

Component::Type C_Material::GetComponentType()
{
	return Component::Type::Material;
}

void C_Material::LoadDefaultTex()
{
	GLubyte checkerImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4];

	for (int i = 0; i < CHECKERS_HEIGHT; i++)
	{
		for (int j = 0; j < CHECKERS_WIDTH; j++)
		{
			int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
			checkerImage[i][j][0] = (GLubyte)c;
			checkerImage[i][j][1] = (GLubyte)c;
			checkerImage[i][j][2] = (GLubyte)c;
			checkerImage[i][j][3] = (GLubyte)255;
		}
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &defaultTextureID);
	glBindTexture(GL_TEXTURE_2D, defaultTextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, CHECKERS_WIDTH, CHECKERS_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkerImage);	
}


