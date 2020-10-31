#pragma once
#include "Mesh.h"

#include <string>

using namespace std;

class Mesh_Cube: public Mesh
{
public:
	Mesh_Cube();
	~Mesh_Cube();

	void LoadTexture(const char* file_name) override;
	void Draw() override;
	void DrawCubeWithArrays();
	void DrawCubeWithIndices();
};
