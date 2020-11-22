#pragma once

#include "Globals.h"

struct aiScene;
class C_Material;
struct aiMaterial;
class Resource_Model;

namespace Importer {
	namespace Model {
		const aiScene* ProcessAssimpScene(const char* buffer, uint size);
		void Import(const aiScene* scene, Resource_Model* model);
		uint64 Save(const Resource_Model* model, char** buffer);
		void Load(const char* buffer, Resource_Model* model);

		namespace Private
		{
			void ImportNodeData(const aiScene* scene, const aiNode* node, Resource_Model* model, uint64 parentID);
		}
	}
}