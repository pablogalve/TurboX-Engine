#ifndef __RESOURCE_MESH_H__
#define __RESOURCE_MESH_H__

#include "Resource.h"
#include "Globals.h"
#include "Math.h"
#include "MathGeoLib/MathGeoLib.h"

class Resource;

class ResourceMesh : public Resource
{
public:
	ResourceMesh(uint UUID);
	virtual ~ResourceMesh();

	void LoadInMemory() override;
	void FreeInMemory() override;
	void Save(Config& config) const override;
	void Load(const Config& config) override;
	void CleanUp() override;
	void Draw();

	void GenerateBuffersGPU();	

public: 
	uint id_index = -1;
	uint num_index = 0;
	uint* index = nullptr;

	uint id_vertex = -1;
	uint num_vertex = 0;
	float3* vertex = nullptr;

	uint id_normals = -1;
	uint num_normals = 0;
	float3* normals = nullptr;

	uint num_textureCoords = 0;
	float2* texturesCoords = nullptr;

	uint num_faces = 0;
};
#endif// !__RESOURCE_MESH_H__