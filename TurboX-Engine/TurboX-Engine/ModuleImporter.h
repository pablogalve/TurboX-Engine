#ifndef __ModuleImporter_H__
#define __ModuleImporter_H__

#include "Module.h"
#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#pragma comment (lib, "Libraries/Assimp/libx86/assimp.lib")

struct Mesh
{
	uint id_index = 0; // index in VRAM
	uint num_index = 0;
	uint* index = nullptr;

	uint id_vertex = 0; // unique vertex in VRAM
	uint num_vertex = 0;
	float* vertex = nullptr;

	uint id_normals = 0;
	uint num_normals = 0;
	float* normals = NULL;

	uint id_colors = 0;
	uint num_colors = 0;
	float* colors = NULL;

	uint id_texcoords = 0;
	uint num_texcoords = 0;
	float* texcoords = NULL;
};

class ModuleImporter : public Module
{
public:

	ModuleImporter(Application* app, bool start_enabled = true);
	~ModuleImporter();

	bool Init(JSON_Object* obj)override;
	bool CleanUp()override;

	void LoadFBX(char* path);

public:

	Mesh ourMesh;


};

#endif // __ModuleImporter_H__
