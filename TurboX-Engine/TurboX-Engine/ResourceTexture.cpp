#include "ResourceTexture.h"
#include "Config_JSON.h"
#include "ModuleRenderer3D.h"
#include "ModuleTexture.h"
#include "Application.h"

ResourceTexture::ResourceTexture(uint UUID) : Resource(UUID, ResType::Texture)
{
	format = rgba;
}

ResourceTexture::~ResourceTexture()
{
}

void ResourceTexture::LoadInMemory()
{
	if (!loaded) {
		gpuID = App->texture_importer->LoadTexture(exportedFile.c_str(), width, height);
		loaded = true;
	}
	references++;

}

void ResourceTexture::FreeInMemory()
{
	references--;
	if (references == 0) {
		if (gpuID != -1)
			glDeleteBuffers(1, &gpuID);
		loaded = false;
	}
}

void ResourceTexture::Save(Config & config) const
{
	config.AddInt("Format", format);
}

void ResourceTexture::Load(const Config & config)
{
	if (exportedFile.size() == 0) {
		exportedFile = LIB_TEXTURES_PATH + fileName + DDS_FORMAT;
	
	}
	format = (ResourceTexture::Format) config.GetInt("Format", 0);
}

void ResourceTexture::CleanUp()
{
	if (loaded) {
		FreeInMemory();
	}	
}
