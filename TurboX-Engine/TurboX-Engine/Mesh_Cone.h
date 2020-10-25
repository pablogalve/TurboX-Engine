#pragma once
#include "Mesh.h"

class Mesh_Cone : public Mesh
{
public:
	Mesh_Cone(float radius_base, float height, uint sides, float radius = 0.0f);
	~Mesh_Cone();

	void Draw() override;

private:
	
	float radius;
	float radius_base;
	float height;
	uint sides;

	std::vector<GLfloat> cone_vertices;
	std::vector<GLfloat> cone_normals;
	std::vector<GLfloat> cone_texcoords;
	std::vector<GLushort> cone_indices;
};
