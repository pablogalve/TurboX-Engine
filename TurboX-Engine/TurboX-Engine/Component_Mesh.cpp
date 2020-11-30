#include "Application.h"
#include "Component_Mesh.h"
#include "glew\glew.h"
#include "SDL\include\SDL_opengl.h"
#include "ModuleScene.h"
#include "ModuleConsole.h"
#include "ModuleFileSystem.h"

#pragma comment (lib, "Libraries/glew/glew32.lib")    /* link OpenGL Utility lib*/
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

C_Mesh::C_Mesh(Component::Type type, GameObject* owner):Component(type, owner)
{
	this->owner = owner;
	material = nullptr;
	vertex_normals_active = false;
}

C_Mesh::~C_Mesh()
{
}

void C_Mesh::Draw()
{	
	if (this != nullptr) 
	{
		if (active == true)
		{
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			if (num_index == 0) {// if the mesh has no index
				glBindBuffer(GL_ARRAY_BUFFER, id_vertex);
				glVertexPointer(3, GL_FLOAT, 0, NULL);
				glDrawArrays(GL_TRIANGLES, 0, num_vertex);
				glBindBuffer(GL_ARRAY_BUFFER, 0); //resets the buffer
			}
			else {

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_index); // test: before it was 2 lines upper
				glBindBuffer(GL_ARRAY_BUFFER, id_vertex);
				glVertexPointer(3, GL_FLOAT, 0, NULL);
				GLenum error = glGetError();

				if (num_normals > 0)
				{
					glEnableClientState(GL_NORMAL_ARRAY);
					glBindBuffer(GL_ARRAY_BUFFER, id_normals);
					glNormalPointer(GL_FLOAT, 0, NULL);
				}

				if (vertex_normals_active)
				{
					glBegin(GL_LINES);
					glColor4f(0.66f, 1.0f, 0.16f, 1.0f); // Green
					DrawVertexNormals();
					glEnd();
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // Set color of everything back to white
				}

				glDrawElements(GL_TRIANGLES, num_index, GL_UNSIGNED_INT, NULL);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindTexture(GL_TEXTURE_2D, 0);

			}

			glDisableClientState(GL_NORMAL_ARRAY);
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);


		}
	}
	
}

void C_Mesh::SetMeshBuffer()
{
	glGenBuffers(1, (GLuint*)&(id_vertex));
	glGenBuffers(1, (GLuint*)&(id_normals));// generates 1 buffer. then it assign a GLuint to its mem adress.

	glBindBuffer(GL_ARRAY_BUFFER, id_vertex); // set the type of buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(float3) * num_vertex, &vertex[0], GL_STATIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, id_normals);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float3) * num_normals, &normals[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (num_index > 0) {
		glGenBuffers(1, (GLuint*)&(id_index));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_index);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * num_index, &index[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

Component::Type C_Mesh::GetComponentType()
{
	return Component::Type::Mesh;
}

void C_Mesh::DrawVertexNormals()
{
	for (int j = 0; j < num_normals; j++)
	{
		glBegin(GL_LINES);
		glVertex3f(vertex[j].x, vertex[j].y, vertex[j].z);
		glVertex3f(vertex[j].x - normals[j].x, vertex[j].y - normals[j].y, vertex[j].z - normals[j].z);
		glLineWidth(1.0f);
		glEnd();
	}
}