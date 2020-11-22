#pragma once

#include "Globals.h"
#include <string>

class C_Material;
struct aiMaterial;

namespace Importer {
	namespace Textures {
		void Import(C_Material* mat, std::string file, bool imported);
		uint Save(const C_Material* mat, char** filebuffer);
		void Load(const char* fileBuffer, C_Material* mat, uint size);
	}
}