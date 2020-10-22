#pragma once
#include "Mesh.h"

class Cone : public Mesh
{
public:
	Cone(float radius_base, float height, uint sides, float radius = 0.0f);
	~Cone();

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
