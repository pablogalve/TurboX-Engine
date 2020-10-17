#include "Globals.h"
#include "Application.h"
#include "ModuleImporter.h"


ModuleImporter::ModuleImporter(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	name = "Importer";
}

// Destructor
ModuleImporter::~ModuleImporter()
{}

// Called before render is available
bool ModuleImporter::Init(JSON_Object* obj)
{

	bool ret = true;
	json_object_clear(obj);
	return ret;
}

// Called before quitting
bool ModuleImporter::CleanUp()
{

	return true;
}

void ModuleImporter::LoadFBX(char* file_path)
{
	
	const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);
	
	if (scene != nullptr && scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		aiReleaseImport(scene);
	}
	else
		LOG("Error loading file %s", file_path);

}