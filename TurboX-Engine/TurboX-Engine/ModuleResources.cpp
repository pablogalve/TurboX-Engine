#include "Globals.h"
#include "ModuleResources.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleFileSystem.h"
#include "Resource_Model.h"
#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Importer_Model.h"
#include "ModuleScene.h"
#include "GameObject.h"

#pragma comment (lib, "Libraries/Assimp/libx86/assimp.lib")

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

void ModuleResources::ImportFileFromAssets(const char* path)
{
	FileType fileType = App->input->GetFileType(path);
	ResourceType type = GetResourceTypeFromFileExtension(fileType);

	const aiScene* scene = nullptr;

	char* buffer = nullptr;
	uint size = App->file_system->Load(path, &buffer);

	if (buffer != nullptr)
	{
		scene = aiImportFileFromMemory(buffer, size, aiProcessPreset_TargetRealtime_MaxQuality, NULL);
	}
	else
	{
		scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
	}

	aiNode* node = scene->mRootNode;

	switch (type)
	{
		case (ResourceType::TEXTURE):
		{

			break;
		}
		case (ResourceType::MODEL):
		{
			Importer::Model::Import(scene, node, App->scene->GetRoot(), path);
			break;
		}
	}

	aiReleaseImport(scene);
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