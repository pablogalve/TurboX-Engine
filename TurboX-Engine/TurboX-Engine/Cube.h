#pragma once
#include "Mesh.h"

class Cube: public Mesh
{
public:
	Cube();
	~Cube();

	void LoadTexture(const char* file_name) override;
	void Draw() override;
	void DrawCubeWithArrays();
	void DrawCubeWithIndices();

public:

	
};
