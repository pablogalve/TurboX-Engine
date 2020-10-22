#pragma once
#include "Mesh.h"

class Cylinder : public Mesh
{
public:
	Cylinder(float radius, float height, uint sides);
	~Cylinder();

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
