#pragma once

#include "Globals.h"
#include "MathGeoLib/Math/float4x4.h"

struct aiScene;
struct aiNode;
struct aiMaterial;
class Resource_Model;
class GameObject;

namespace Importer {
	namespace Model {
		void Import(const aiScene* scene, aiNode* node, GameObject* parent, std::string file, float4x4 transfor_heredated = float4x4::identity);
		uint64 Save(const Resource_Model* model, char** buffer);
		void Load(const char* buffer, Resource_Model* model);
	}
}