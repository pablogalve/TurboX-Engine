#include "Component_Mesh.h"
#include "glew\glew.h"
#include "SDL\include\SDL_opengl.h"
#include "ModuleScene.h"
#include "Application.h"
#include "ModuleConsole.h"

#pragma comment (lib, "Libraries/glew/glew32.lib")    /* link OpenGL Utility lib*/
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

C_Mesh::C_Mesh(Component::Type type, GameObject* owner):Component(type, owner)
{
	this->owner = owner;
	material = nullptr;
	isCheckersTexLoaded = false;
	face_normals_active = false;
	vertex_normals_active = false;
}

C_Mesh::~C_Mesh()
{
}

void C_Mesh::Draw()
{		
	material = (C_Material*)owner->GetComponent(Component::Type::Material);

	if (active == true) {			
		
		glEnableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, id_vertex);
		glVertexPointer(3, GL_FLOAT, 0, NULL);

		if(num_normals > 0)
		{
			glEnableClientState(GL_NORMAL_ARRAY);
			glBindBuffer(GL_ARRAY_BUFFER, id_normals);
			glNormalPointer(GL_FLOAT, 0, NULL);
		}

		if (num_texcoords > 0)
		{
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBuffer(GL_ARRAY_BUFFER, id_texcoords);
			glTexCoordPointer(2, GL_FLOAT, 0, NULL);
		}
	
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_index);
	
		if(material != nullptr && material->active)
			glBindTexture(GL_TEXTURE_2D, material->TextureID);
	
		if (vertex_normals_active) {
			glBegin(GL_LINES);
			glColor4f(0.66f, 1.0f, 0.16f, 1.0f); // Green
			DrawVertexNormals();
			glEnd();
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // Set color of everything back to white
		}
		if (face_normals_active) {
			glBegin(GL_LINES);
			glColor4f(0.0f, 1.0f, 1.0f, 1.0f); // Cyan
			DrawFaceNormals();
			glEnd();
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // Set color of everything back to white
		}

		glDrawElements(GL_TRIANGLES, num_index, GL_UNSIGNED_INT, NULL);
		glBindTexture(GL_TEXTURE_2D, 0);

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);		
	}
}

void C_Mesh::LoadCheckersTex()
{
	GLubyte checkerImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4];

	for (int i = 0; i < CHECKERS_HEIGHT; i++)
	{
		for (int j = 0; j < CHECKERS_WIDTH; j++)
		{
			int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
			checkerImage[i][j][0] = (GLubyte)c;
			checkerImage[i][j][1] = (GLubyte)c;
			checkerImage[i][j][2] = (GLubyte)c;
			checkerImage[i][j][3] = (GLubyte)255;
		}
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_2D, TextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, CHECKERS_WIDTH, CHECKERS_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkerImage);

	isCheckersTexLoaded = true;
}

void C_Mesh::SetMeshBuffer(GameObject* parent)
{
	glGenBuffers(1, (GLuint*) & (parent->mesh->id_vertex));
	glBindBuffer(GL_ARRAY_BUFFER, parent->mesh->id_vertex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * parent->mesh->num_vertex * 3, parent->mesh->vertex, GL_STATIC_DRAW);

	glGenBuffers(1, (GLuint*) & (parent->mesh->id_index));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, parent->mesh->id_index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * parent->mesh->num_index, parent->mesh->index, GL_STATIC_DRAW);

	if (parent->mesh->num_normals > 0)
	{
		glGenBuffers(1, (GLuint*) & (parent->mesh->id_normals));
		glBindBuffer(GL_ARRAY_BUFFER, parent->mesh->id_normals);
		glBufferData(GL_ARRAY_BUFFER, sizeof(uint) * parent->mesh->num_normals * 3, parent->mesh->normals, GL_STATIC_DRAW);
	}

	if (num_texcoords > 0)
	{
		glGenBuffers(1, (GLuint*) & (parent->mesh->id_texcoords));
		glBindBuffer(GL_ARRAY_BUFFER, parent->mesh->id_texcoords);
		glBufferData(GL_ARRAY_BUFFER, sizeof(uint) * parent->mesh->num_texcoords * 2, parent->mesh->texcoords, GL_STATIC_DRAW);
	}
}

void C_Mesh::LoadMesh(char* file_path)
{
	const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes()) {
		if (scene->mNumMeshes == 1) {
			LoadSingleMesh(file_path);
		}
		else {
			LoadSingleMesh(file_path);
			// Use scene->mNumMeshes to iterate on scene->mMeshes array
			for (int i = 1; i < scene->mNumMeshes; i++)
			{
				aiMesh* meshIterator = scene->mMeshes[i];

				GameObject* new_gameObject = new GameObject();
				new_gameObject->CreateComponent(Component::Type::Mesh);
				new_gameObject->CreateComponent(Component::Type::Material);
				new_gameObject->CreateComponent(Component::Type::Transform);
				new_gameObject->material->LoadTexture((const char*)owner->material->GetMaterialPath().c_str());
				App->scene->AddChild(new_gameObject);

				// copy vertices
				new_gameObject->mesh->num_vertex = meshIterator->mNumVertices;
				new_gameObject->mesh->vertex = new float[new_gameObject->mesh->num_vertex * 3];
				memcpy(new_gameObject->mesh->vertex, meshIterator->mVertices, sizeof(float) * new_gameObject->mesh->num_vertex * 3);
				MY_LOG("New mesh with %d vertices", new_gameObject->mesh->num_vertex);
				App->console->AddLog("New mesh with %d vertices", new_gameObject->mesh->num_vertex);

				// copy faces
				if (meshIterator->HasFaces())
				{
					new_gameObject->mesh->num_index = meshIterator->mNumFaces * 3;
					new_gameObject->mesh->index = new uint[new_gameObject->mesh->num_index]; // assume each face is a triangle
					for (uint i = 0; i < meshIterator->mNumFaces; ++i)
					{
						if (meshIterator->mFaces[i].mNumIndices != 3)
						{
							MY_LOG("WARNING, geometry face with != 3 indices!");
							App->console->AddLog("WARNING, geometry face with != 3 indices!");
						}
						else
						{
							memcpy(&new_gameObject->mesh->index[i * 3], meshIterator->mFaces[i].mIndices, 3 * sizeof(uint));
						}
					}
				}

				if (meshIterator->HasNormals())
				{
					new_gameObject->mesh->num_normals = meshIterator->mNumVertices;
					new_gameObject->mesh->normals = new float[new_gameObject->mesh->num_normals * 3];
					memcpy(new_gameObject->mesh->normals, meshIterator->mNormals, sizeof(float) * new_gameObject->mesh->num_normals * 3);
				}

				if (meshIterator->HasTextureCoords(0))
				{
					new_gameObject->mesh->num_texcoords = meshIterator->mNumVertices;
					new_gameObject->mesh->texcoords = new float[new_gameObject->mesh->num_texcoords * 2];
					for (unsigned int i = 0, v = 0; i < new_gameObject->mesh->num_texcoords; i++, v += 2)
					{
						new_gameObject->mesh->texcoords[v] = meshIterator->mTextureCoords[0][i].x;
						new_gameObject->mesh->texcoords[v + 1] = meshIterator->mTextureCoords[0][i].y;
					}
				}
				SetMeshBuffer(new_gameObject);
			}

			aiReleaseImport(scene);
		}
		
	}	else {
		MY_LOG("Error loading scene % s", file_path);
		App->console->AddLog("Error loading scene % s", file_path);
	}
}

void C_Mesh::LoadSingleMesh(char* file_path)
{
	const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);
	
	aiMesh* meshIterator = scene->mMeshes[0];

	// copy vertices
	num_vertex = meshIterator->mNumVertices;
	vertex = new float[num_vertex * 3];
	memcpy(vertex, meshIterator->mVertices, sizeof(float) * num_vertex * 3);
	MY_LOG("New mesh with %d vertices", num_vertex);
	App->console->AddLog("New mesh with %d vertices", num_vertex);

	// copy faces
	if (meshIterator->HasFaces())
	{
		num_index = meshIterator->mNumFaces * 3;
		index = new uint[num_index]; // assume each face is a triangle
		for (uint i = 0; i < meshIterator->mNumFaces; ++i)
		{
			if (meshIterator->mFaces[i].mNumIndices != 3)
			{
				MY_LOG("WARNING, geometry face with != 3 indices!");
				App->console->AddLog("WARNING, geometry face with != 3 indices!");
			}
			else
			{
				memcpy(&index[i * 3], meshIterator->mFaces[i].mIndices, 3 * sizeof(uint));
			}
		}
	}

	if (meshIterator->HasNormals())
	{
		num_normals = meshIterator->mNumVertices;
		normals = new float[num_normals * 3];
		memcpy(normals, meshIterator->mNormals, sizeof(float) * num_normals * 3);
	}

	if (meshIterator->HasTextureCoords(0))
	{
		num_texcoords = meshIterator->mNumVertices;
		texcoords = new float[num_texcoords * 2];
		for (unsigned int i = 0, v = 0; i < num_texcoords; i++, v += 2)
		{
			texcoords[v] = meshIterator->mTextureCoords[0][i].x;
			texcoords[v + 1] = meshIterator->mTextureCoords[0][i].y;
		}
	}
	SetMeshBuffer(owner);		

	aiReleaseImport(scene);
}

Component::Type C_Mesh::GetComponentType()
{
	return Component::Type::Mesh;
}

void C_Mesh::DrawFaceNormals()
{
	for (size_t i = 0; i < num_vertex * 3; i += 3)
	{
		float x = (vertex[i] + vertex[i + 3] + vertex[i + 6]) / 3;
		float y = (vertex[i + 1] + vertex[i + 4] + vertex[i + 7]) / 3;
		float z = (vertex[i + 2] + vertex[i + 5] + vertex[i + 8]) / 3;
		glVertex3f(x, y, z);

		float normal_x = normals[i];
		float normal_y = normals[i + 1];
		float normal_z = normals[i + 2];
		glVertex3f(x + normal_x, y + normal_y, z + normal_z);
	}
}

void C_Mesh::DrawVertexNormals()
{
	for (size_t i = 0; i < num_vertex * 3; i += 3)
	{
		float x = vertex[i];
		float y = vertex[i + 1];
		float z = vertex[i + 2];
		glVertex3f(x, y, z);

		float normal_x = normals[i];
		float normal_y = normals[i + 1];
		float normal_z = normals[i + 2];
		glVertex3f(x + normal_x, y + normal_y, z + normal_z);
	}
}