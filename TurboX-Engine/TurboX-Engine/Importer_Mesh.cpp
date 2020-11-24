#include "Importer_Mesh.h"
#include "Application.h"
#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Component_Mesh.h"
#include "Component.h"
#include "ModuleFileSystem.h"

#pragma comment (lib, "Libraries/Assimp/libx86/assimp.lib")

int Importer::Mesh::Import(const aiMesh* ai_material, C_Mesh* mesh, char* name, bool imported)
{
	int material_index = -1;

	if (!imported)
	{
		if (ai_material == nullptr)
		{
			const char* error = aiGetErrorString();
			MY_LOG("Error loading FBX: %s", error);
			return material_index;
		}

		mesh->num_vertex = ai_material->mNumVertices * 3;
		mesh->vertex = new float[mesh->num_vertex];
		memcpy(mesh->vertex, ai_material->mVertices, sizeof(float) * mesh->num_vertex);
		MY_LOG("Loading FBX correctly");
		MY_LOG("New mesh with %d vertices", mesh->num_vertex / 3);

		if (ai_material->HasFaces())
		{
			mesh->num_index = ai_material->mNumFaces * 3;
			mesh->index = new uint[mesh->num_index];
			for (uint j = 0; j < ai_material->mNumFaces; ++j)
			{
				if (ai_material->mFaces[j].mNumIndices != 3) {
					MY_LOG("WARNING, geometry face with != 3 indices!");
				}
				else {
					memcpy(&mesh->index[j * 3], ai_material->mFaces[j].mIndices, 3 * sizeof(uint));
				}

			}
			MY_LOG("New mesh with %d index", mesh->num_index);
		}
		mesh->num_normals = mesh->num_vertex;
		mesh->normals = new float[ai_material->mNumVertices * 3];
		for (int x = 0, y = 0; x < ai_material->mNumVertices; x++, y += 3) {
			if (ai_material->HasNormals())
			{
				mesh->normals[y] = ai_material->mNormals[x].x;
				mesh->normals[y + 1] = ai_material->mNormals[x].y;
				mesh->normals[y + 2] = ai_material->mNormals[x].z;
			}
		}

		if (ai_material->HasTextureCoords(0)) {
			mesh->num_texcoords = ai_material->mNumVertices;
			mesh->texcoords = new float[mesh->num_texcoords * 2];
			for (uint i = 0, j = 0; i < mesh->num_texcoords; i++, j += 2) {
				mesh->texcoords[j] = ai_material->mTextureCoords[0][i].x;
				mesh->texcoords[j + 1] = ai_material->mTextureCoords[0][i].y;
			}
			material_index = ai_material->mMaterialIndex;
		}

		char* buffer = nullptr;
		uint size = Importer::Mesh::Save(mesh, &buffer);
		char name_buff[200];
		sprintf_s(name_buff, 200, "Library/Meshes/%s.turboxmesh", mesh->file_name.c_str());
		App->file_system->Save(name_buff, buffer, size);
	}
	else 
	{
		char* buffer = App->file_system->ReadPhysFile(name);
		Importer::Mesh::Load(buffer, mesh);
	}

	material_index = ai_material->mMaterialIndex;
	mesh->SetMeshBuffer();


	return material_index;
}

uint Importer::Mesh::Save(const C_Mesh* mesh, char** filebuffer)
{
	uint ranges[4] = { mesh->num_index, mesh->num_vertex, mesh->num_normals, mesh->num_texcoords };

	uint size = sizeof(ranges) + sizeof(uint) * mesh->num_index + sizeof(float) * mesh->num_vertex * 3
		+ sizeof(float) * mesh->num_normals * 3 + sizeof(float) * mesh->num_texcoords * 2;

	char* buffer = new char[size];
	char* cursor = buffer;

	uint bytes = sizeof(ranges);
	memcpy(cursor, ranges, bytes);
	cursor += bytes;

	//store indices
	bytes = sizeof(uint) * mesh->num_index;
	memcpy(cursor, mesh->index, bytes);
	cursor += bytes;

	//store vertices
	bytes = sizeof(float) * mesh->num_vertex;
	memcpy(cursor, mesh->vertex, bytes);
	cursor += bytes;

	//store normals
	bytes = sizeof(float) * mesh->num_normals;
	memcpy(cursor, mesh->normals, bytes);
	cursor += bytes;

	//store texcoords
	bytes = sizeof(float) * mesh->num_texcoords * 2;
	memcpy(cursor, mesh->texcoords, bytes);

	*filebuffer = buffer;

	return size;
}

void Importer::Mesh::Load(const char* fileBuffer, C_Mesh* mesh)
{
	char* cursor = (char*)fileBuffer;

	uint ranges[4];
	uint bytes = sizeof(ranges);
	memcpy(ranges, cursor, bytes);
	cursor += bytes;

	mesh->num_index = ranges[0];
	mesh->num_vertex = ranges[1];
	mesh->num_normals = ranges[2];
	mesh->num_texcoords = ranges[3];

	// Load indices
	bytes = sizeof(uint) * mesh->num_index;
	mesh->index = new uint[mesh->num_index];
	memcpy(mesh->index, cursor, bytes);
	cursor += bytes;

	//load vertices
	bytes = sizeof(float) * mesh->num_vertex * 3;
	mesh->vertex = new float[mesh->num_vertex * 3];
	memcpy(mesh->vertex, cursor, bytes);
	cursor += bytes;

	//load normals
	bytes = sizeof(float) * mesh->num_normals * 3;
	mesh->normals = new float[mesh->num_normals * 3];
	memcpy(mesh->normals, cursor, bytes);
	cursor += bytes;

	//load texcoords
	bytes = sizeof(float) * mesh->num_texcoords * 2;
	mesh->texcoords = new float[mesh->num_texcoords * 2];
	memcpy(mesh->texcoords, cursor, bytes);
}
