#pragma once
#include "Mesh.h"

class Mesh_Cylinder : public Mesh
{
public:
	Mesh_Cylinder(float radius, float height, uint sides);
	~Mesh_Cylinder();

	void Draw() override;

private:

	float radius;
	float height;
	uint sides;
	std::vector<GLfloat> cylinder_vertices;
	std::vector<GLfloat> cylinder_normals;
	std::vector<GLfloat> cylinder_texcoords;
	std::vector<GLushort> cylinder_indices;
};
