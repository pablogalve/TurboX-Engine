#pragma once

#include "Module.h"
#include "Resource.h"
#include "ResourceMesh.h"
#include "GameObject.h"
#include <string>
#include <map>

#define MS_TO_CHECK_META 2000

class Timer;

class ModuleResources : public Module
{
public:
	ModuleResources(Application* app, bool start_enabled = true);
	~ModuleResources();

	bool Start() override;
	update_status PreUpdate(float dt) override;
	bool CleanUp() override;

	Resource* CreateNewResource(Resource::ResType type, uint forceUUID = 0);
	void RemoveResource(const char* path);
	void RemoveResource(uint UUID);

	void ChangeResourceUUID(uint formerUUID, uint newUUID);
	void LoadFiles(const char* filePath);
	bool ImportFileAndGenerateMeta(const char* newFileInAssets);

	uint FindByPath(const char* fileInAssets, Resource::ResType type = Resource::ResType::None) const;
	uint FindByName(const char* name, Resource::ResType type = Resource::ResType::None) const;

	const Resource* Get(uint uuid) const;
	Resource* Get(uint uuid);
	std::map<uint, Resource*> GetResourcesList() const { return resources; }
	std::vector<Resource*> GetResourcesListType(Resource::ResType type, bool loaded = false);

	const Resource::ResType GetResourceTypeFromExtension(const char* path) const;
	Resource* GetResourceByName(std::string* name);

	void GenerateBillboard();

	ResourceMesh* billboard;

	ResourceMesh* GetBillboard() const;

private:
	uint last_uuid = 1;
	std::map<uint, Resource*> resources;
	Timer lastCheck;
	
	GameObject* street;
private:
	bool ManageResourceWithMeta(const char* resource, const char* meta);
	void GenerateMetaFile(const char* assetFile, uint ResourceUUID, std::vector<uint> exportedUUIDs);
	void CheckMetaFiles();
};