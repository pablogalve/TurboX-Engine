#pragma once
#include "Mesh.h"
#include <vector>

class Sphere : public Mesh
{
public:
	Sphere(float _radius, unsigned int _rings, unsigned int _sectors);
	~Sphere();

	void Draw() override;

private:

	float _radius;
	unsigned int _rings;
	unsigned int _sectors;
};
