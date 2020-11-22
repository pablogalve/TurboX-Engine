#include "Importer_Model.h"
#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#pragma comment (lib, "Libraries/Assimp/libx86/assimp.lib")

const aiScene* Importer::Model::ProcessAssimpScene(const char* buffer, uint size)
{
	return aiImportFileFromMemory(buffer, size, aiProcessPreset_TargetRealtime_MaxQuality, nullptr);
}

void Importer::Model::Import(const aiScene* scene, Resource_Model* model)
{
	Private::ImportNodeData(scene, scene->mRootNode, model, 0);
	(*model->nodes.begin()).name = model->GetName();
}

uint64 Importer::Model::Save(const Resource_Model* model, char** buffer)
{
	return uint64();
}

void Importer::Model::Load(const char* buffer, Resource_Model* model)
{
}
