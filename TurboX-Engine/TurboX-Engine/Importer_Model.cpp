#include "Importer_Model.h"
#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#pragma comment (lib, "Libraries/Assimp/libx86/assimp.lib")
#include "MathGeoLib/Math/Quat.h"
#include "Application.h"
#include "ModuleScene.h"
#include "ModuleFileSystem.h"
#include "Importer_Mesh.h"
#include "Importer_Material.h"

void Importer::Model::Import(const aiScene* scene, aiNode* node, GameObject* parent, std::string file, float4x4 transform_heredated)
{
	if (node->mNumMeshes == 0 && node->mNumChildren == 0)
		return;

	aiVector3D translation, scaling;
	aiQuaternion rotation;
	node->mTransformation.Decompose(scaling, rotation, translation);
	float3 pos = { translation.x,translation.y,translation.z };
	Quat rot = { rotation.x,rotation.y,rotation.z,rotation.w };
	float3 scale = { scaling.x,scaling.y,scaling.z };
	GameObject* game_object = parent;

	transform_heredated = transform_heredated * float4x4::FromTRS(pos, rot, scale);
	transform_heredated.Decompose(pos, rot, scale);

	if (node->mNumChildren > 1 || node->mNumMeshes != 0) {
		game_object = App->scene->CreateGameObject(file, pos, rot, scale, parent);
		transform_heredated = float4x4::identity;
	}

	if (node->mNumMeshes > 0) {
		C_Mesh* mesh = (C_Mesh*)game_object->CreateComponent(Component::Type::Mesh);
		aiMesh* ai_mesh = scene->mMeshes[node->mMeshes[0]];
		bool mesh_imported = false;
		bool tex_imported = false;

		//mesh->full_file_name = file;
		//mesh->file_name = App->file_system->GetFileName(file, true);

		char name_buff[200];
		/*if (App->file_system->counterMesh != 0) {
			sprintf_s(name_buff, 200, "%s (%i)", mesh->file_name.c_str(), App->file_system->counterMesh);
			mesh->file_name = name_buff;
		}
		App->file_system->counterMesh++;*/

		int num_material = ai_mesh->mMaterialIndex;

		sprintf_s(name_buff, 200, "Library/Meshes/%s.falcasmesh", mesh->file_name.c_str());
		if (App->file_system->Exists(name_buff)) {
			mesh_imported = true;
		}
		Importer::Mesh::Import(ai_mesh, mesh, name_buff, mesh_imported);

		if (num_material != -1 && num_material < scene->mNumMaterials) {
			C_Material* mat = (C_Material*)game_object->CreateComponent(Component::Type::Material);
			aiString material_path;
			scene->mMaterials[num_material]->GetTexture(aiTextureType_DIFFUSE, 0, &material_path);
			if (material_path.length > 0) {
				std::string path = App->file_system->GetPathFile(file);
				path += material_path.C_Str();
				sprintf_s(name_buff, 200, "Library/Textures/%s", mesh->file_name.c_str());
				if (App->file_system->Exists(name_buff)) {
					tex_imported = true;
				}
				Importer::Textures::Import(mat, path, tex_imported);
			}
		}
	}
}

uint64 Importer::Model::Save(const Resource_Model* model, char** buffer)
{
	return uint64();
}

void Importer::Model::Load(const char* buffer, Resource_Model* model)
{
}
