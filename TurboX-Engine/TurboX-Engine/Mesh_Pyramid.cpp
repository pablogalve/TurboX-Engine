#include "Mesh_Pyramid.h"

Mesh_Pyramid::Mesh_Pyramid()
{
}

Mesh_Pyramid::~Mesh_Pyramid()
{
}

void Mesh_Pyramid::Draw()
{
	GLfloat vertices[] = {
		1.f, 2.f, 1.f,
		0.f, 0.f, 0.f,
		2.f, 0.f, 0.f,
		2.f, 0.f, 2.f,
		0.f, 0.f, 2.f, };          // 5 of vertex coords

	GLubyte indices[] = { 0,1,2, 2,3,0,   // 24 of indices
						 0,3,4, 0,4,1,
						 1,2,3, 3,4,1, };

	// activate and specify pointer to vertex array
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	// draw a pyramid
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_BYTE, indices);

	// deactivate vertex arrays after drawing
	glDisableClientState(GL_VERTEX_ARRAY);
}