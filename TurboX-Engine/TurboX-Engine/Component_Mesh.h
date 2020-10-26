#ifndef __COMPONENT_MESH_H_
#define __COMPONENT_MESH_H_

#include "Component.h"
#include "Globals.h"

class C_Mesh : public Component {
public:
	C_Mesh(Component::Type type);
	~C_Mesh();

	void Draw();
	void SetMeshBuffer();
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
};
#endif // !__COMPONENT_LIGHT_H_
