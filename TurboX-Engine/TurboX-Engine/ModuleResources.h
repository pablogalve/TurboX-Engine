#pragma once

#include "Module.h"
#include "Globals.h"
#include "Resource.h"

enum class FileType;

enum class ResourceType {
	MODEL,
	MESH,
	TEXTURE,
	UNKNOWN,
};

class ModuleResources : public Module
{
public:
	ModuleResources(Application* app, bool start_enabled = true);
	~ModuleResources();

	bool Start()override;
	update_status Update(float dt)override;
	bool CleanUp()override;

	void ImportFileFromAssets(const char* path);

	ResourceType GetResourceTypeFromFileExtension(FileType fileType) const;
};
