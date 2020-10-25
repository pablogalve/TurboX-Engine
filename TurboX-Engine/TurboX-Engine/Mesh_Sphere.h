#pragma once
#include "Mesh.h"
#include <vector>

class Mesh_Sphere : public Mesh
{
public:
	Mesh_Sphere(float _radius, unsigned int _rings, unsigned int _sectors);
	~Mesh_Sphere();

	void Draw() override;

private:

	float _radius;
	unsigned int _rings;
	unsigned int _sectors;
};
