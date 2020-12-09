#pragma once

#include "Module.h"
#include "Globals.h"
#include "Resource.h"
#include "ResourceMesh.h"
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


class SceneImporter : public Module
{
public:

public:
	SceneImporter(Application* app, bool start_enabled = true);
	~SceneImporter();

	bool Start()override;
	update_status Update(float dt)override;
	bool CleanUp()override;

	bool ImportScene(const char* scene, std::vector<std::string>* written, uint forceUUID = 0);

	void LoadFBXScene(const char* FBXpath);

	void LoadMeshTURBOX(const char* fileNameTURBOX, ResourceMesh* resource);

private:

	bool ImportMeshRecursive(aiNode* node, const aiScene* scene, std::vector<std::string>* meshesNames, uint forceUUID = 0);

	GameObject* ImportNodeRecursive(aiNode* node, const aiScene* scene, GameObject* parent);

};
