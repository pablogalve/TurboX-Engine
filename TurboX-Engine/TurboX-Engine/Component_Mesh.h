#ifndef __COMPONENT_MESH_H_
#define __COMPONENT_MESH_H_

#include "Component.h"
#include "Component_Material.h"
#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#pragma comment (lib, "Libraries/Assimp/libx86/assimp.lib")

class C_Mesh : public Component {
public:
	C_Mesh(Component::Type type, GameObject* owner);
	~C_Mesh();

	void Draw();
	void LoadCheckersTex();
	void SetMeshBuffer();
	void LoadMesh(char* file_path);

	Component::Type GetComponentType() override;

public:
	
	uint TextureID;

	uint id_index = 0; // index in VRAM
	uint num_index = 0;
	uint* index = nullptr;

	uint id_vertex = 0; // unique vertex in VRAM
	uint num_vertex = 0;
	float* vertex = nullptr;

	uint id_normals = 0;
	uint num_normals = 0;
	float* normals = NULL;

	uint id_texcoords = 0;
	uint num_texcoords = 0;
	float* texcoords = NULL;

	C_Material* material = nullptr;

private:

	bool isCheckersTexLoaded = false;
};
#endif // !__COMPONENT_LIGHT_H_
