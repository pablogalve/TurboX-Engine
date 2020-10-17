#include "Globals.h"
#include "Application.h"
#include "ModuleImporter.h"
#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#pragma comment (lib, "Libraries/Assimp/libx86/assimp.lib")

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