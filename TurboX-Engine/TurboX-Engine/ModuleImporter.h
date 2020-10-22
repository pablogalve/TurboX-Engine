#ifndef __ModuleImporter_H__
#define __ModuleImporter_H__

#include "Module.h"
#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "CustomMesh.h"
#pragma comment (lib, "Libraries/Assimp/libx86/assimp.lib")

class ModuleImporter : public Module
{
public:

	ModuleImporter(Application* app, bool start_enabled = true);
	~ModuleImporter();

	bool Init(JSON_Object* obj)override;
	bool CleanUp()override;

	void LoadFBX(char* path);

public:

	CustomMesh ourMesh;


};

#endif // __ModuleImporter_H__
