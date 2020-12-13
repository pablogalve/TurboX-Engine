#include "Application.h"
#include "Component_Mesh.h"
#include "glew\glew.h"
#include "SDL\include\SDL_opengl.h"
#include "ModuleScene.h"
#include "ModuleConsole.h"
#include "ModuleFileSystem.h"

#include "ResourceMesh.h"
#include "ModuleResources.h"

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

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			if (material != NULL) {
				
				if (material->HasTexture()) 
				{
					glBindTexture(GL_TEXTURE_2D, material->GetTexID());
					glTexCoordPointer(2, GL_FLOAT, 0, &(resourceMesh->texturesCoords[0]));

				}
				else {
					glColor3f(material->colors.x, material->colors.y, material->colors.z);
				}

			}

			if (resourceMesh->num_index == 0) {// if the mesh has no index
				glBindBuffer(GL_ARRAY_BUFFER, resourceMesh->id_vertex);
				glVertexPointer(3, GL_FLOAT, 0, NULL);
				glDrawArrays(GL_TRIANGLES, 0, resourceMesh->num_vertex);
				glBindBuffer(GL_ARRAY_BUFFER, 0); //resets the buffer
			}
			else {

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, resourceMesh->id_index); // test: before it was 2 lines upper
				glBindBuffer(GL_ARRAY_BUFFER, resourceMesh->id_vertex);
				glVertexPointer(3, GL_FLOAT, 0, NULL);
				GLenum error = glGetError();

				if (resourceMesh->num_normals > 0)
				{
					glEnableClientState(GL_NORMAL_ARRAY);
					glBindBuffer(GL_ARRAY_BUFFER, resourceMesh->id_normals);
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

				glDrawElements(GL_TRIANGLES, resourceMesh->num_index, GL_UNSIGNED_INT, NULL);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindTexture(GL_TEXTURE_2D, 0);

			}

			glColor3f(1.0f, 1.0f, 1.0f);
			glDisableClientState(GL_NORMAL_ARRAY);
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);


		}
	}
	
}

void C_Mesh::SetMeshBuffer()
{
	glGenBuffers(1, (GLuint*)&(resourceMesh->id_vertex));
	glGenBuffers(1, (GLuint*)&(resourceMesh->id_normals));// generates 1 buffer. then it assign a GLuint to its mem adress.

	glBindBuffer(GL_ARRAY_BUFFER, resourceMesh->id_vertex); // set the type of buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(float3) * resourceMesh->num_vertex, &resourceMesh->vertex[0], GL_STATIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, resourceMesh->id_normals);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float3) * resourceMesh->num_normals, &resourceMesh->normals[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (resourceMesh->num_index > 0) {
		glGenBuffers(1, (GLuint*)&(resourceMesh->id_index));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, resourceMesh->id_index);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * resourceMesh->num_index, &resourceMesh->index[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

Component::Type C_Mesh::GetComponentType()
{
	return Component::Type::Mesh;
}

void C_Mesh::DrawVertexNormals()
{
	for (int j = 0; j < resourceMesh->num_normals; j++)
	{
		glBegin(GL_LINES);
		glVertex3f(resourceMesh->vertex[j].x, resourceMesh->vertex[j].y, resourceMesh->vertex[j].z);
		glVertex3f(resourceMesh->vertex[j].x - resourceMesh->normals[j].x, resourceMesh->vertex[j].y - resourceMesh->normals[j].y, resourceMesh->vertex[j].z - resourceMesh->normals[j].z);
		glLineWidth(1.0f);
		glEnd();
	}
}

bool C_Mesh::Save(Config* data)
{
	bool ret = true;

	data->AddString("Component", "Mesh");
	data->AddUInt("UUID", component_UUID);
	data->AddUInt("Owner UUID", owner->GetUUID());
	data->AddInt("Type", Component::Type::Mesh);

	if (material != nullptr)
		data->AddUInt("Texture_UUID", material->GetResourceUUID());
	
	if (resourceMesh != nullptr) 
		data->AddString("Custom_File", resourceMesh->GetName());	

	return ret;
}

bool C_Mesh::Load(Config* data)
{
	MY_LOG("Load Component Mesh");
	component_UUID = data->GetUInt("UUID");
	SetMaterial(owner->GetComponentMaterial(data->GetUInt("Texture_UUID")));
	string custom_file = data->GetString("Custom_File", "Empty");
	resourceMesh = (ResourceMesh*)App->resources->Get(App->resources->FindByName(custom_file.c_str(), Resource::ResType::Mesh)); 
	resourceMesh->LoadInMemory();
	return true;
}

void C_Mesh::SetMaterial(C_Material* tex)
{
	material = tex;
}

void C_Mesh::SetResource(uint resource)
{
	resourceMesh = (ResourceMesh*)App->resources->Get(resource);
	resourceMesh->LoadInMemory();
	component_UUID = resource;
}

