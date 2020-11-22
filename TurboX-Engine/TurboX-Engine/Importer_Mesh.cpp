#include "Importer_Mesh.h"

int Importer::Mesh::Import(const aiMesh* ai_material, C_Mesh* mesh, char* name, bool imported)
{
	return 0;
}

uint Importer::Mesh::Save(const C_Mesh* mesh, char** filebuffer)
{
	return uint();
}

void Importer::Mesh::Load(const char* fileBuffer, C_Mesh* mesh)
{
}
