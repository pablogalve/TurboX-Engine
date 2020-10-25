#pragma once
#include "Mesh.h"

class Mesh_CustomMesh : public Mesh
{
public:
	Mesh_CustomMesh();
	~Mesh_CustomMesh();

	void Draw() override;
	void SetMeshBuffer();
public:

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
