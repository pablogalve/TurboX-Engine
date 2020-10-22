#pragma once
#include "Mesh.h"

class Cube: public Mesh
{
public:
	Cube();
	~Cube();

	void Draw() override;
	void DrawCubeWithArrays();
	void DrawCubeWithIndices();

public:


};
