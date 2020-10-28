#include "Mesh_CustomMesh.h"

Mesh_CustomMesh::Mesh_CustomMesh()
{
}

Mesh_CustomMesh::~Mesh_CustomMesh()
{
}

void Mesh_CustomMesh::SetMeshBuffer()
{
	/*glGenBuffers(1, (GLuint*)&(id_vertex));
	glBindBuffer(GL_ARRAY_BUFFER, id_vertex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_vertex * 3, vertex, GL_STATIC_DRAW);

	glGenBuffers(1, (GLuint*)&(id_index));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * num_index, index, GL_STATIC_DRAW);

	if (num_normals > 0)
	{
		glGenBuffers(1, (GLuint*)&(id_normals));
		glBindBuffer(GL_ARRAY_BUFFER, id_normals);
		glBufferData(GL_ARRAY_BUFFER, sizeof(uint) * num_normals * 3, normals, GL_STATIC_DRAW);
	}

	if (num_texcoords > 0)
	{
		glGenBuffers(1, (GLuint*)&(id_texcoords));
		glBindBuffer(GL_ARRAY_BUFFER, id_texcoords);
		glBufferData(GL_ARRAY_BUFFER, sizeof(uint) * num_texcoords * 2, texcoords, GL_STATIC_DRAW);
	}*/
}

void Mesh_CustomMesh::Draw()
{	
	/*glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, id_vertex);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	if(num_normals > 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, id_normals);
		glNormalPointer(GL_FLOAT, 0, NULL);
	}

	if (num_texcoords > 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, id_texcoords);
		glTexCoordPointer(2, GL_FLOAT, 0, NULL);
	}
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_index);
	
	glBindTexture(GL_TEXTURE_2D, TextureID);
	glDrawElements(GL_TRIANGLES, num_index, GL_UNSIGNED_INT, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);*/
}