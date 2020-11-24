#pragma once

#include "Globals.h"

struct aiMesh;
struct aiMaterial;
class C_Mesh;

namespace Importer {
	namespace Mesh {
		int Import(const aiMesh* ai_material, C_Mesh* mesh, char* name, bool imported);
		uint Save(const C_Mesh* mesh, char** filebuffer);
		void Load(const char* fileBuffer, C_Mesh* mesh);
	}
}