#pragma once

#include "Module.h"
#include "Globals.h"
#include "Resource.h"
#include "MathGeoLib\MathGeoLib.h"

#include <iostream>
#include <fstream> 

#include "Component_Mesh.h"
#include "Component_Material.h"
#include "Component_Transformation.h"
#include "ModuleFileSystem.h"

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"

#pragma comment (lib, "Libraries/Assimp/libx86/assimp.lib")


class ModuleResources : public Module
{
public:
	
	struct dataScene 
	{

		float3 position = { 0,0,0 };
		float3 scale = { 0,0,0 };
		Quat rotation = Quat(0, 0, 0, 0);

		uint numMeshes = 0;

	};

	struct dataMesh
	{
	public:
		float colors[3];

		uint num_index = 0;
		uint* index = nullptr;

		uint num_vertex = 0;
		float3* vertex = nullptr;
		uint num_normals = 0;
		float3* normals = nullptr;
		uint num_texCoords = 0;
		float2* texturesCoords = nullptr;

		uint texID;
	};

public:
	ModuleResources(Application* app, bool start_enabled = true);
	~ModuleResources();

	bool Start()override;
	update_status Update(float dt)override;
	bool CleanUp()override;

	void ImportFBXtoPEI(const char* path);
	void ImportFBXandLoad(const char* fbxPath);
	void LoadPEI(const char* fileName);

	void LoadFBX(const char* path);

private:
	void ImportFromMesh(const aiScene* currSc, aiMesh* new_mesh, std::ofstream* dataFile);
};
