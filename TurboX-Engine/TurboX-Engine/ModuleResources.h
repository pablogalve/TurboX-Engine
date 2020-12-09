#pragma once

#include "Module.h"

class ModuleResources : public Module
{
public:
	ModuleResources(Application* app, bool start_enabled = true);
	~ModuleResources();

	bool Start() override;
	update_status PreUpdate(float dt) override;
	bool CleanUp() override;


private:

	
};
