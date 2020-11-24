#pragma once

#include "Globals.h"
#include <string>

struct aiMaterial;
class C_Material;

namespace Importer {
	namespace Textures {
		void Import(C_Material* mat, std::string file, bool imported);
		uint Save(const C_Material* mat, char** filebuffer);
		void Load(const char* fileBuffer, C_Material* mat, uint size);
	}
}