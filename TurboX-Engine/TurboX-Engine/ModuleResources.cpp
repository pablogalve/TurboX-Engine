#include "Globals.h"
#include "ModuleResources.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleFileSystem.h"
#include "Resource_Model.h"
#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#pragma comment (lib, "Libraries/Assimp/libx86/assimp.lib")
#include "Importer_Model.h"
#include "ModuleScene.h"

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
	const aiScene* scene = nullptr;
	FileType fileType = App->input->GetFileType(path);
	ResourceType type = GetResourceTypeFromFileExtension(fileType);

	char* buffer = nullptr;
	uint64 fileSize = App->file_system->Load(path, &buffer);

	scene = aiImportFileFromMemory(buffer, fileSize, aiProcessPreset_TargetRealtime_MaxQuality, nullptr);

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