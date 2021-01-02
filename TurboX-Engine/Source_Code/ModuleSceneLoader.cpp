#include "Globals.h"
#include "ModuleSceneLoader.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleFileSystem.h"
#include "ModuleRenderer3D.h"
#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "ModuleScene.h"
#include "ModuleResources.h"
#include "GameObject.h"
#include "ModuleTexture.h"
#include "ResourceMesh.h"
#pragma comment (lib, "Libraries/Assimp/libx86/assimp.lib")

SceneImporter::SceneImporter(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	name = "scene_loader";
}

SceneImporter::~SceneImporter()
{
}

bool SceneImporter::Start()
{
	return true;
}

update_status SceneImporter::Update(float dt)
{

	return UPDATE_CONTINUE;
}

bool SceneImporter::CleanUp()
{
	return true;
}

bool SceneImporter::ImportScene(const char* FBXpath, std::vector<std::string>* written, uint forceUUID)
{
	bool ret = true;

	std::string modelName;

	App->file_system->GetNameFromPath(FBXpath, nullptr, &modelName, nullptr, nullptr);

	const aiScene* scene = aiImportFile(FBXpath, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene == nullptr) {

		MY_LOG("Error loading fbx from Assets/Models folder.");
		aiReleaseImport(scene);
		ret = false;
		return ret;
	}

	uint numMaterials = scene->mNumMaterials;
	uint* materialIDs = new uint[scene->mNumMaterials];

	if (ret && scene->HasMaterials()) {
		MY_LOG("Importing FBX texture to DDS from %s", FBXpath);
		for (int i = 0; i < numMaterials; i++) {

			aiMaterial* material = scene->mMaterials[i];



			aiString texturePath;
			aiReturn retu = material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath);
			if (retu == aiReturn_SUCCESS) {

				std::string textureName;
				std::string extension;
				App->file_system->GetNameFromPath(texturePath.C_Str(), nullptr, &textureName, nullptr, nullptr);
				App->file_system->GetNameFromPath(texturePath.C_Str(), nullptr, nullptr, nullptr, &extension);

				std::string texDDSPath;
				if (extension != DDS_FORMAT) {
					std::string texAssetsPath = TEXTURES_PATH + textureName + extension;
					ret = App->texture_importer->ImportToDDS(texAssetsPath.c_str(), textureName.c_str());
					if (!ret) {
						ret = App->texture_importer->ImportToDDS(texturePath.C_Str(), textureName.c_str());
					}
					texDDSPath = LIB_TEXTURES_PATH + textureName + DDS_FORMAT;

				}
				else {
					texDDSPath = TEXTURES_PATH + textureName + DDS_FORMAT;
					App->file_system->CopyDDStoLib(texDDSPath.c_str(), nullptr);
				}
			}
			else {
				MY_LOG("Error loading texture from fbx. Error: %s", aiGetErrorString());
			}
		}
	}

	if (ret && scene->HasMeshes()) 
	{
		MY_LOG("Importing FBX mesh to turbox from %s", FBXpath);

		ret = ImportMeshRecursive(scene->mRootNode, scene, written, forceUUID);
		aiReleaseImport(scene);
	}
	else {
		MY_LOG("Error loading FBX, scene has no meshes");
		ret = false;
	}
	return ret;
}

bool SceneImporter::ImportMeshRecursive(aiNode* node, const aiScene* scene, std::vector<std::string>* meshesNames, uint forceUUID)
{
	bool ret = true;

	if (node->mMetaData != nullptr) {


		if (node->mNumMeshes > 0) {
			for (uint i = 0; i < node->mNumMeshes; i++)
			{
				bool error = false;

				std::string meshName = node->mName.C_Str();
				aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

				std::string uuid;
				if (forceUUID != 0) { uuid += std::to_string(forceUUID) + "~"; }
				std::string fileName = LIB_MODELS_PATH;
				fileName += uuid + meshName;
				fileName += OWN_FILE_FORMAT;
				std::ofstream dataFile(fileName.c_str(), std::fstream::out | std::fstream::binary);

				uint ranges[4] = { mesh->mNumFaces * 3,mesh->mNumVertices, mesh->mNumVertices,  mesh->mNumVertices };
				uint* index = nullptr;
				if (mesh->HasFaces()) { //------------indices

					index = new uint[ranges[0]]; // assume each face is a triangle
					for (uint i = 0; i < mesh->mNumFaces; ++i) {
						if (mesh->mFaces[i].mNumIndices != 3) {
							MY_LOG("WARNING, geometry face with != 3 indices!");
							error = true;
						}
						else {
							memcpy(&index[i * 3], mesh->mFaces[i].mIndices, 3 * sizeof(uint));
						}
					}
				}
				float2* texturesCoords = nullptr;
				if (mesh->GetNumUVChannels() > 0) { //------------textureCoords					
					texturesCoords = new float2[ranges[3]];
					for (int i = 0; i < ranges[3]; i++) {
						texturesCoords[i].x = mesh->mTextureCoords[0][i].x;
						texturesCoords[i].y = mesh->mTextureCoords[0][i].y;
					}
				}
				else { // no textureCoords
					ranges[3] = 0;
				}


				if (!error) {

					uint size = sizeof(ranges) + sizeof(uint) * ranges[0] + sizeof(float3) * ranges[1] + sizeof(float3) * ranges[2] + sizeof(float2) * ranges[3]; // numIndex + numVertex + index + vertex + normals + textureCoords

					char* data = new char[size];
					char* cursor = data;

					uint bytes = sizeof(ranges);
					memcpy(cursor, ranges, bytes);

					cursor += bytes;
					bytes = sizeof(uint) * ranges[0];
					memcpy(cursor, index, bytes);

					cursor += bytes;
					bytes = sizeof(float3) * ranges[1];
					memcpy(cursor, mesh->mVertices, bytes);

					cursor += bytes;
					bytes = sizeof(float3) * ranges[2];
					memcpy(cursor, mesh->mNormals, bytes);

					cursor += bytes;
					bytes = sizeof(float2) * ranges[3];
					memcpy(cursor, texturesCoords, bytes);

					dataFile.write(data, size);

					dataFile.close();
					RELEASE_ARRAY(data);
					cursor = nullptr;
					ret = true;

					meshesNames->push_back(fileName);
				}

				RELEASE_ARRAY(texturesCoords);
				RELEASE_ARRAY(index);
			}
		}
	}
	for (uint i = 0; i < node->mNumChildren; i++) // recursivity
	{
		ret &= ImportMeshRecursive(node->mChildren[i], scene, meshesNames, forceUUID);

	}
	return ret;
}

void SceneImporter::LoadFBXScene(const char* FBXpath)
{
	Timer loadTime;

	std::string fullFBXPath;// = MODELS_PATH;
	fullFBXPath += FBXpath;

	std::string modelName;

	App->file_system->GetNameFromPath(fullFBXPath.c_str(), nullptr, &modelName, nullptr, nullptr);

	const aiScene* scene = aiImportFile(fullFBXPath.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene == nullptr) {
		scene = aiImportFile(FBXpath, aiProcessPreset_TargetRealtime_MaxQuality);
		if (scene == nullptr) 
		{
			MY_LOG("Error loading fbx from Assets/Models folder.");
			aiReleaseImport(scene);

			return;
		}
	}
	else {
		GameObject* GO;
		GO = App->scene->AddGameObject(modelName.c_str());
		GameObject* GOchild = ImportNodeRecursive(scene->mRootNode, scene, GO);


		GOchild = nullptr;
		GO = nullptr;
		aiReleaseImport(scene);
		MY_LOG("Loaded succesfully fbx from %s. Loading time: %.1fms", FBXpath, loadTime.Read());
	}
}

GameObject* SceneImporter::ImportNodeRecursive(aiNode* node, const aiScene* scene, GameObject* parent)
{
	GameObject* nodeGO = nullptr;


	if (node->mMetaData != nullptr) { // to get the gameobject not a transform matrix

		nodeGO = new GameObject();
		nodeGO->name = node->mName.C_Str();
		nodeGO->SetParent(parent);

		aiVector3D position;
		aiQuaternion rotation;
		aiVector3D scale;
		node->mTransformation.Decompose(scale, rotation, position);

		nodeGO->transform->SetPosition(float3(position.x, position.y, position.z));
		nodeGO->transform->SetScale(float3(scale.x, scale.y, scale.z));
		nodeGO->transform->SetQuaternionRotation(Quat(rotation.x, rotation.y, rotation.z, rotation.w));


		if (node->mNumMeshes > 0)
		{
			for (uint i = 0; i < node->mNumMeshes; i++)
			{

				aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
				aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

				C_Material* compMat = (C_Material*)nodeGO->CreateComponent(Component::Type::Material);

				if (material)
				{
					if (compMat != nullptr)
					{
						bool error, col, mater;
						error = col = mater = false;

						aiString texturePath;


						aiColor3D color = aiColor3D();
						material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
						if (!color.IsBlack())
						{
							compMat->colors = { color.r, color.g, color.b };
							col = true;
						}

						aiReturn ret = material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath);
						if (ret == aiReturn_SUCCESS) {
							mater = true;

							std::string path;
							std::string textureName;
							std::string extension;
							App->file_system->GetNameFromPath(texturePath.C_Str(), &path, &textureName, nullptr, nullptr);
							App->file_system->GetNameFromPath(texturePath.C_Str(), nullptr, nullptr, nullptr, &extension);

							uint UUID = App->resources->FindByName(textureName.c_str(), Resource::ResType::Texture);
							if (UUID == 0) {
								if (App->resources->ImportFileAndGenerateMeta(texturePath.C_Str())) {
									compMat->SetResource(App->resources->FindByName(textureName.c_str(), Resource::ResType::Texture));
								}
							}
							else {

								compMat->SetResource(UUID);
								compMat->SetName(textureName.c_str());
								App->scene->materials.push_back(compMat);
							}
						}
						else {

							MY_LOG("Error loading texture from fbx. Error: %s", aiGetErrorString());
						}
					}
					else {
						RELEASE(compMat);
					}
				}

				std::string meshName = nodeGO->name;

				C_Mesh* newMesh = nullptr;

				uint resourceUUID = App->resources->FindByName(meshName.c_str(), Resource::ResType::Mesh);
				
				if (resourceUUID != 0)
				{
					newMesh = (C_Mesh*)nodeGO->CreateComponent(Component::Type::Mesh);
					newMesh->SetResource(resourceUUID);
				}

				if (newMesh != nullptr)
				{
					if (compMat) 
					{
						newMesh->SetMaterial(compMat);
					}
				}
				else {
					RELEASE(newMesh);
				}

				compMat = nullptr;
				newMesh = nullptr;
				mesh = nullptr;
				material = nullptr;

				/*compMesh->num_vertex = mesh->mNumVertices;
				compMesh->vertex = new float3[compMesh->num_vertex];
				memcpy(compMesh->vertex, mesh->mVertices, sizeof(float3) * compMesh->num_vertex);
				MY_LOG("New mesh with %d vertices", compMesh->num_vertex);

				if (mesh->HasFaces()) {
					compMesh->num_index = mesh->mNumFaces * 3;
					compMesh->index = new uint[compMesh->num_index]; // assume each face is a triangle
					for (uint i = 0; i < mesh->mNumFaces; ++i) {
						if (mesh->mFaces[i].mNumIndices != 3) {
							MY_LOG("WARNING, geometry face with != 3 indices!");

						}
						else {
							memcpy(&compMesh->index[i * 3], mesh->mFaces[i].mIndices, 3 * sizeof(uint));
						}
					}
				}
				if (mesh->HasNormals()) {
					compMesh->num_normals = mesh->mNumVertices;
					compMesh->normals = new float3[compMesh->num_normals];
					memcpy(compMesh->normals, mesh->mNormals, sizeof(float3) * compMesh->num_normals);
					MY_LOG("New mesh with %d normals", compMesh->num_normals);
				}
				if (mesh->GetNumUVChannels() > 0) {
					compMesh->num_textureCoords = compMesh->num_vertex;
					compMesh->texturesCoords = new float2[compMesh->num_textureCoords];

					for (int i = 0; i < (compMesh->num_textureCoords); i++) {
						compMesh->texturesCoords[i].x = mesh->mTextureCoords[0][i].x;
						compMesh->texturesCoords[i].y = mesh->mTextureCoords[0][i].y;
					}
					MY_LOG("New mesh with %d UVs", compMesh->num_textureCoords);
				}
				else {
					MY_LOG("Error loading mesh");
				}*/


				//Calculate bounding box
				//nodeGO->boundingBox.SetNegativeInfinity();
				//nodeGO->boundingBox.Enclose((float3*)compMesh->vertex, compMesh->num_vertex);
				

			}
		}
	}
	if (!nodeGO) { nodeGO = parent; }
	for (uint i = 0; i < node->mNumChildren; i++) // recursivity
	{
		GameObject* child = ImportNodeRecursive(node->mChildren[i], scene, nodeGO);

	}
	return nodeGO;
}

C_Material* SceneImporter::ImportMaterialToResource(aiMaterial* material, GameObject* owner)
{
	C_Material* mat = nullptr;
	bool error, col, mater;
	error = col = mater = false;

	aiString texturePath;
	mat = new C_Material(Component::Type::Material, owner);


	aiColor3D color = aiColor3D();
	material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
	if (!color.IsBlack())
	{
		mat->colors = { color.r, color.g, color.b };
		col = true;
	}

	aiReturn ret = material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath);
	if (ret == aiReturn_SUCCESS) {
		mater = true;

		std::string path;
		std::string textureName;
		std::string extension;
		App->file_system->GetNameFromPath(texturePath.C_Str(), &path, &textureName, nullptr, nullptr);
		App->file_system->GetNameFromPath(texturePath.C_Str(), nullptr, nullptr, nullptr, &extension);

		uint UUID = App->resources->FindByName(textureName.c_str(), Resource::ResType::Texture);
		if (UUID == 0) {
			if (App->resources->ImportFileAndGenerateMeta(texturePath.C_Str())) {
				mat->SetResource(App->resources->FindByName(textureName.c_str(), Resource::ResType::Texture));
			}
		}
		else {

			mat->SetResource(UUID);
		}
	}
	else {

		MY_LOG("Error loading texture from fbx. Error: %s", aiGetErrorString());
	}
	

	return mat;
}

C_Mesh* SceneImporter::ImportMeshToResource(aiMesh* mesh, const char* peiName, GameObject* owner)
{

	bool error = false;
	C_Mesh* newMesh = nullptr;
	uint resourceUUID = App->resources->FindByName(peiName, Resource::ResType::Mesh);
	if (resourceUUID != 0) {//checks if resource already exists
		newMesh = new C_Mesh(Component::Type::Mesh, owner);
		newMesh->SetResource(resourceUUID);
		//nodeGO->boundingBox.SetNegativeInfinity();
		//nodeGO->boundingBox.Enclose((float3*)compMesh->vertex, compMesh->num_vertex);
		//newMesh->CreateBBox();
	}
	return newMesh;
}

void SceneImporter::LoadMeshTURBOX(const char* fileNameTURBOX, ResourceMesh* resource) {

	Timer loadingTimer;
	std::string turboxName;
	App->file_system->GetNameFromPath(fileNameTURBOX, nullptr, &turboxName, nullptr, nullptr);
	std::string filePath = LIB_MODELS_PATH;
	filePath += turboxName;
	filePath += OWN_FILE_FORMAT;



	std::ifstream dataFile(filePath.c_str(), std::fstream::out | std::fstream::binary);
	if (dataFile.fail()) {
		MY_LOG("Error loading TURBOX. Cannot find TURBOX file in %s in Lib/Textures", filePath.c_str());
		return;
	}


	uint ranges[4] = { 0,0,0,0 }; // [numIndex , numVertex, numNormals, numTexCoords]

	uint rangesSize = sizeof(ranges);
	char* headerdata = new char[rangesSize];


	dataFile.read(headerdata, rangesSize);
	memcpy(ranges, headerdata, rangesSize);

	resource->num_index = ranges[0];
	resource->num_vertex = ranges[1];
	resource->num_normals = ranges[2];
	resource->num_textureCoords = ranges[3];

	resource->index = new uint[resource->num_index];
	resource->vertex = new float3[resource->num_vertex];
	resource->normals = new float3[resource->num_normals];
	resource->texturesCoords = new float2[resource->num_textureCoords];
	resource->num_faces = resource->num_index / 3;

	uint meshDataSize = sizeof(uint) * resource->num_index + sizeof(float3) * resource->num_vertex + sizeof(float3) * resource->num_normals + sizeof(float2) * resource->num_textureCoords;

	char* meshdata = new char[meshDataSize];
	char* mcursor = meshdata;


	dataFile.seekg(rangesSize);

	dataFile.read(meshdata, meshDataSize);


	uint mbytes = sizeof(uint) * resource->num_index;//index		
	memcpy(resource->index, mcursor, mbytes);

	mcursor += mbytes;
	mbytes = sizeof(float3) * resource->num_vertex;//vertex		
	memcpy(resource->vertex, mcursor, mbytes);

	mcursor += mbytes;
	mbytes = sizeof(float3) * resource->num_normals;//normals	
	memcpy(resource->normals, mcursor, mbytes);

	mcursor += mbytes;
	mbytes = sizeof(float2) * resource->num_textureCoords; //texCoords
	memcpy(resource->texturesCoords, mcursor, mbytes);

	MY_LOG("Succesfully loaded TURBOX: %s. Loading time: %i ms \n", fileNameTURBOX, loadingTimer.Read());

	RELEASE_ARRAY(headerdata);
	RELEASE_ARRAY(meshdata);
	mcursor = nullptr;

	dataFile.close();
}