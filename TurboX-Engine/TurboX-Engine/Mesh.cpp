#include "Mesh.h"



Mesh::Mesh()
{
	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);
}

Mesh::~Mesh()
{

}

void Mesh::LoadTexture(const char* file_name)
{
}

void Mesh::Draw()
{
}

