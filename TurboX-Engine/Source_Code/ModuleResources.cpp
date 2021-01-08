#include "Application.h"
#include "ModuleResources.h"
#include "ResourceMesh.h"
#include "ModuleScene.h"
#include "Timer.h"
#include "ModuleFileSystem.h"
#include "ModuleRenderer3D.h"
#include "ModuleTexture.h"
#include "GameObject.h"
#include "ModuleSceneLoader.h"
#include "Component.h"
#include "Component_Material.h"
#include <iostream>

ModuleResources::ModuleResources(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	billboard = nullptr;
	street = nullptr;
}


ModuleResources::~ModuleResources()
{
}

bool ModuleResources::Start()
{
	CheckMetaFiles();
	GenerateBillboard();

	App->scene->LoadTownScene();
	

	return true;
}

update_status ModuleResources::PreUpdate(float dt)
{
	if (!App->scene->inGame) 
	{
		if (lastCheck.Read() > MS_TO_CHECK_META) 
		{
			lastCheck.ResetTimer();
			CheckMetaFiles();
		}
	}
	else
	{
		lastCheck.Stop();
	}

	return UPDATE_CONTINUE;
}

bool ModuleResources::CleanUp()
{
	
	return true;
}

void ModuleResources::CheckMetaFiles()
{

	std::vector<std::string> files;
	std::vector<std::string> dirs;

	App->file_system->GetFilesFromDir(ASSETS_PATH, files, dirs, true);

	std::map<std::string, uint> missingComplementary;

	int i = 0;
	for (std::vector<std::string>::const_iterator fileIt = files.begin(); fileIt != files.end(); fileIt++, i++) {

		bool meta = App->file_system->IsMetaFile((*fileIt).c_str());
		std::string fileName;
		meta ? App->file_system->GetNameFromPath((*fileIt).c_str(), nullptr, &fileName, nullptr, nullptr)
			: App->file_system->GetNameFromPath((*fileIt).c_str(), nullptr, nullptr, &fileName, nullptr);

		bool hasComplementary = false;
		for (std::map<std::string, uint>::iterator missFileIt = missingComplementary.begin(); missFileIt != missingComplementary.end(); missFileIt++) {
			if (fileName == (*missFileIt).first)
			{
				if (ManageResourceWithMeta(files[(*missFileIt).second].c_str(), (*fileIt).c_str()) == false) {
					ImportFileAndGenerateMeta(files[(*missFileIt).second].c_str());
				}
				missingComplementary.erase(missFileIt);
				hasComplementary = true;

				break;
			}
		}
		if (!hasComplementary) {
			missingComplementary[fileName] = i;
		}
	}

	if (missingComplementary.size() > 0) {
		for (std::map<std::string, uint>::iterator fileIt = missingComplementary.begin(); fileIt != missingComplementary.end(); fileIt++) {

			bool meta = App->file_system->IsMetaFile(files[(*fileIt).second]);
			if (meta) {
				MY_LOG("resource missing! %s", files[(*fileIt).second].c_str());
				RemoveResource(files[(*fileIt).second].c_str());

			}
			else {
				MY_LOG("meta missing! %s", files[(*fileIt).second].c_str())
					ImportFileAndGenerateMeta(files[(*fileIt).second].c_str());
			}
		}
	}
	lastCheck.Start();
}

uint ModuleResources::FindByPath(const char* fileInAssets, Resource::ResType type) const
{
	std::string fileName = fileInAssets;

	for (std::map<uint, Resource*>::const_iterator it = resources.begin(); it != resources.end(); it++) {
		if (it->second->GetPathStr() == fileName) {
			if (type == Resource::ResType::None || type == it->second->GetType())
				return it->first;
		}
	}
	return 0;
}

uint ModuleResources::FindByName(const char* fileInAssets, Resource::ResType type) const
{
	if (fileInAssets != nullptr) {
		std::string fileName = fileInAssets;

		for (std::map<uint, Resource*>::const_iterator it = resources.begin(); it != resources.end(); it++) {
			if (it->second->GetNameStr() == fileName) {
				if (type == Resource::ResType::None || type == it->second->GetType())
					return it->first;
			}
		}
	}
	return 0;
}

bool ModuleResources::ManageResourceWithMeta(const char* resource, const char* metaPath)
{
	uint resourceLastMod = App->file_system->GetLastModification(resource);
	char* buffer = nullptr;
	uint size = App->file_system->readFile(metaPath, &buffer);
	if (size < 0) {
		MY_LOG("Error loading meta %s. All data not loaded.", metaPath)
			RELEASE_ARRAY(buffer);
		return false;
	}
	Config meta(buffer);
	RELEASE_ARRAY(buffer);

	uint lastMetaMod = meta.GetUInt("TimeStamp", 0);
	if (lastMetaMod != resourceLastMod) {

		return false;
	}

	uint resourceUUID = meta.GetUInt("ResourceUUID", 0);
	if (Get(resourceUUID)) {
		return true;
	}
	Resource::ResType type = GetResourceTypeFromExtension(resource);
	if (type == Resource::ResType::Scene) {
		uint childs = meta.GetUInt("UUID Childs Num", 0);
		for (int i = 0; i < childs; i++) {

			std::string uuidNum = "UUID_" + std::to_string(i);
			uint childUUID = meta.GetUInt(uuidNum.c_str(), 0);

			if (Get(childUUID)) {
				return true;
			}

			std::string uuidTurboxNum = "UUID_TURBOXName_" + std::to_string(i);
			std::string uuidTurbox = meta.GetString(uuidTurboxNum.c_str(), "");

			std::string turbox;
			App->file_system->GetUUID_TURBOX(uuidTurbox.c_str(), nullptr, &turbox);

			Resource* res = CreateNewResource(Resource::ResType::Mesh, childUUID);

			res->SetName(turbox.c_str());
			res->SetPath(resource);

			std::string exportedFile;
			exportedFile = LIB_MODELS_PATH + std::to_string(resourceUUID) + "~" + turbox + OWN_FILE_FORMAT;
			res->SetExportedFile(exportedFile);
			res->Load(meta);
		}
	}
	else {
		Resource* res = CreateNewResource(type, resourceUUID);
		std::string name;
		App->file_system->GetNameFromPath(resource, nullptr, &name, nullptr, nullptr);
		res->SetName(name.c_str());
		res->SetPath(resource);
		res->Load(meta);
	}

	return true;
}

bool ModuleResources::ImportFileAndGenerateMeta(const char* newFileInAssets)
{
	bool ret = false;
	bool import_ok = false;
	std::vector<std::string> exportedFiles;
	Resource::ResType type = GetResourceTypeFromExtension(newFileInAssets);
	uint resourceUUID = App->scene->GetRandomUUID();
	switch (type) {
	case Resource::ResType::Texture: {import_ok = App->texture_importer->ImportTexture(newFileInAssets, &exportedFiles); break; }
	case Resource::ResType::Scene: {import_ok = App->scene_loader->ImportScene(newFileInAssets, &exportedFiles, resourceUUID); break; }
	case Resource::ResType::Mesh: {import_ok = App->file_system->CopyTURBOXtoLib(newFileInAssets, &exportedFiles, resourceUUID); break; }
	case Resource::ResType::None: {return false; }
	}
	if (import_ok) {
		std::vector<uint> uuids;
		for (int i = 0; i < exportedFiles.size(); i++) {

			Resource* res = CreateNewResource(type);

			res->SetPath(newFileInAssets);
			res->SetExportedFile(exportedFiles[i].c_str());

			std::string name;
			App->file_system->GetNameFromPath(exportedFiles[i].c_str(), nullptr, &name, nullptr, nullptr);

			if (type != Resource::ResType::Scene) {

				res->SetName(name.c_str());
				res->SetUUID(resourceUUID);
			}
			else {
				std::string  turbox;
				App->file_system->GetUUID_TURBOX(name.c_str(), nullptr, &turbox);
				res->SetName(turbox.c_str());
				uuids.push_back(res->GetUUID());
			}
			res = nullptr;
		}

		GenerateMetaFile(newFileInAssets, resourceUUID, uuids);
		ret = true;
	}
	return ret;
}

const Resource* ModuleResources::Get(uint _uuid) const
{
	for (std::map<uint, Resource*>::const_iterator it = resources.begin(); it != resources.end(); it++) {
		if (it->first == _uuid) {
			return it->second;
		}
	}
	return nullptr;
}

Resource* ModuleResources::Get(uint _uuid)
{
	for (std::map<uint, Resource*>::iterator it = resources.begin(); it != resources.end(); it++) {
		if (it->first == _uuid) {
			return it->second;
		}
	}
	return nullptr;
}

void ModuleResources::LoadFiles(const char* filePath)
{
	Resource::ResType type = GetResourceTypeFromExtension(filePath);

	switch (type) {
	case Resource::ResType::Texture: {
		std::string tName;
		App->file_system->GetNameFromPath(filePath, nullptr, &tName, nullptr, nullptr);
		GameObject* GO;
		GO = App->scene->AddGameObject(tName.c_str());
		C_Material* mat = (C_Material*)GO->CreateComponent(Component::Type::Material);
		mat->SetResource(App->resources->FindByPath(filePath)); break; 
		mat->SetName(tName.c_str());
		App->scene->materials.push_back(mat);
	}
	case Resource::ResType::Scene: {App->scene_loader->LoadFBXScene(filePath); break; }
	}

}

std::vector<Resource*> ModuleResources::GetResourcesListType(Resource::ResType type, bool loaded)
{
	std::vector<Resource*> ret;
	for (std::map<uint, Resource*>::iterator it = resources.begin(); it != resources.end(); it++) {
		if (it->second->GetType() == type) {
			if (loaded) {
				if (it->second->IsLoaded()) {
					ret.push_back(it->second);
				}
			}
			else
				ret.push_back(it->second);
		}
	}
	return ret;
}

Resource* ModuleResources::CreateNewResource(Resource::ResType type, uint forceUUID)
{
	Resource* res = nullptr;
	uint uuid;

	if (forceUUID != 0 && Get(forceUUID) == nullptr)
		uuid = forceUUID;
	else
		uuid = App->scene->GetRandomUUID();
	if (Get(uuid) != nullptr) {
		MY_LOG("Resource already created! UUID matching");
		return nullptr;
	}

	switch (type) {
	case Resource::ResType::Texture: {	res = (Resource*) new ResourceTexture(uuid); break;	}
	case Resource::ResType::Mesh: {	res = (Resource*) new ResourceMesh(uuid); break;	}
	case Resource::ResType::Scene: {res = (Resource*) new ResourceMesh(uuid); break;	}
	}
	if (res != nullptr) {
		resources[uuid] = res;
	}

	return res;
}

void ModuleResources::RemoveResource(const char* metaPath)
{

	std::string mPath = metaPath;
	char* buffer = nullptr;
	App->file_system->readFile(mPath.c_str(), &buffer);
	Config meta(buffer);
	uint UUID = meta.GetUInt("ResourceUUID", 0);
	uint childs = meta.GetUInt("UUID Childs Num", 0);
	Resource* res = nullptr;
	if (childs > 0) {
		for (int i = 0; i < childs; i++) {
			std::string uuidNum = "UUID_" + std::to_string(i);
			uint childUUID = meta.GetUInt(uuidNum.c_str(), 0);
			res = Get(childUUID);
			if (res != nullptr) {
				res->CleanUp();
				resources.erase(res->GetUUID());
				App->file_system->RemoveFile(res->GetExportedFile().c_str());
			}
		}
	}
	else {
		res = Get(UUID);
		if (res != nullptr) {
			resources.erase(res->GetUUID());
			res->CleanUp();
			App->file_system->RemoveFile(res->GetExportedFile().c_str());
		}
	}

	App->file_system->RemoveFile(metaPath);
	res = nullptr;
	RELEASE_ARRAY(buffer);
}

void ModuleResources::RemoveResource(uint UUID)
{
	resources.erase(UUID);
}

void ModuleResources::GenerateMetaFile(const char* assetFile, uint resourceUUID, std::vector<uint> exportedUUIDs)
{
	Config meta;
	uint timestamp = App->file_system->GetLastModification(assetFile);
	Resource::ResType type = GetResourceTypeFromExtension(assetFile);
	meta.AddUInt("TimeStamp", timestamp);
	meta.AddUInt("ResourceUUID", resourceUUID);
	Resource* res = Get(resourceUUID);
	if (type == Resource::ResType::Scene) {
		meta.AddUInt("UUID Childs Num", exportedUUIDs.size());
		for (int i = 0; i < exportedUUIDs.size(); i++) {
			std::string uuidNum = "UUID_" + std::to_string(i);
			meta.AddUInt(uuidNum.c_str(), exportedUUIDs[i]);
			std::string uuidTurboxNum = "UUID_TURBOXName_" + std::to_string(i);
			meta.AddString(uuidTurboxNum.c_str(), Get(exportedUUIDs[i])->GetName());
			Resource* res = Get(exportedUUIDs[i]);
			res->Save(meta);
		}
	}
	else {
		res->Save(meta);
	}

	char* buffer = nullptr;
	uint size = meta.Save(&buffer);
	std::string name = assetFile;
		
	name += META_FORMAT;
	App->file_system->writeFile(name.c_str(), buffer, size);
	RELEASE_ARRAY(buffer);
}

const Resource::ResType ModuleResources::GetResourceTypeFromExtension(const char* path) const
{
	std::string extension;
	std::string name;
	App->file_system->GetNameFromPath(path, nullptr, nullptr, nullptr, &extension);
	App->file_system->GetNameFromPath(path, nullptr, &name, nullptr, nullptr);
	if (name[0] == 'U' && name[1] == 'I' && name[2] == '_') {
		return Resource::ResType::UI;
	}
	if (extension == OWN_FILE_FORMAT || extension == OWN_FILE_FORMAT_CAP)  return Resource::ResType::Mesh;
	if (extension == FBX_FORMAT || extension == FBX_FORMAT_CAP)  return Resource::ResType::Scene;
	if (extension == DDS_FORMAT || extension == DDS_FORMAT_CAP)  return Resource::ResType::Texture;
	if (extension == PNG_FORMAT || extension == PNG_FORMAT_CAP)  return Resource::ResType::Texture;
	if (extension == JPG_FORMAT || extension == JPG_FORMAT_CAP)  return Resource::ResType::Texture;
	if (extension == JPEG_FORMAT || extension == JPEG_FORMAT_CAP)  return Resource::ResType::Texture;
	if (extension == TGA_FORMAT || extension == TGA_FORMAT_CAP)  return Resource::ResType::Texture;

	return Resource::ResType::None;
}

Resource* ModuleResources::GetResourceByName(std::string* name)
{
	for (std::map<uint, Resource*>::iterator goIterator = resources.begin(); goIterator != resources.end(); goIterator++)
	{
		Resource* res = (*goIterator).second;

		std::string resname = res->GetNameStr();

		if (!name->compare(resname)) 
			return res; //return ret if they are equal
		
		res = nullptr;
	}

	return nullptr;
}

void ModuleResources::GenerateBillboard()
{
	static const float vertex[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
	};

	billboard = new ResourceMesh(LCG().Int());

	//Vertex
	billboard->num_vertex = 4;
	billboard->vertex = new float3[billboard->num_vertex];
	memcpy(billboard->vertex, vertex, sizeof(vertex));

	//Indices
	static const uint indices[] = {
		0,1,2,1,3,2
	};
	billboard->num_index = 6;
	billboard->index = new uint[billboard->num_index];
	memcpy(billboard->index, indices, sizeof(indices));

	//Texture Coordinates
	static const float tex[] = {
	1,1,0,1,1,0,0,0
	};

	billboard->num_textureCoords = billboard->num_vertex * 2;
	billboard->texturesCoords = new float2[billboard->num_textureCoords];
	memcpy(billboard->texturesCoords, tex, sizeof(tex));

	billboard->GenerateBuffersGPU();
}

void ModuleResources::ChangeResourceUUID(uint formerUUID, uint newUUID)
{
	for (std::map<uint, Resource*>::iterator it = resources.begin(); it != resources.end(); it++) {
		if (it->first == formerUUID) {
			resources[newUUID] = resources[formerUUID];
			resources.erase(formerUUID);
			return;
		}
	}
}

ResourceMesh* ModuleResources::GetBillboard() const
{
	return billboard;
}
