#include "Globals.h"
#include "ModuleResources.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleFileSystem.h"
#include "Resource_Model.h"
#include "Assimp/include/scene.h"
#include "Importer_Model.h"

ModuleResources::ModuleResources(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	name = "Resources";
}

ModuleResources::~ModuleResources()
{
}

bool ModuleResources::Start()
{
	return true;
}

update_status ModuleResources::Update(float dt)
{

	return UPDATE_CONTINUE;
}

bool ModuleResources::CleanUp()
{
	return true;
}

uint64 ModuleResources::ImportFileFromAssets(const char* path)
{
	FileType fileType = App->input->GetFileType(path);
	ResourceType type = GetResourceTypeFromFileExtension(fileType);
	uint64 resourceID = 0;

	char* buffer = nullptr;
	uint64 fileSize = 0;

	fileSize = App->file_system->Load(path, &buffer);

	switch (type)
	{
		case (ResourceType::TEXTURE):
		{

			break;
		}
		case (ResourceType::MODEL):
		{

			break;
		}
	}

	return resourceID;
}

ResourceType ModuleResources::GetResourceTypeFromFileExtension(FileType fileType) const
{
	switch (fileType)
	{
	case FileType::FBX:
		return ResourceType::MODEL;
		break;
	case FileType::PNG:
		return ResourceType::TEXTURE;
		break;
	case FileType::DDS:
		return ResourceType::TEXTURE;
		break;
	case FileType::UNDEFINED:
		return ResourceType::UNKNOWN;
		break;
	default:
		return ResourceType::UNKNOWN;
		break;
	}

	return ResourceType();
}

void ModuleResources::ImportModel(const char* buffer, uint size, Resource* model)
{
	Resource_Model* resource_model = (Resource_Model*)model;
	const aiScene* scene = Importer::Model::ProcessAssimpScene(buffer, size);
	Importer::Model::Import(scene, resource_model);
}