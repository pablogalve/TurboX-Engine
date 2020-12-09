#include "Application.h"
#include "ModuleResources.h"
#include "ModuleScene.h"
#include "Timer.h"
#include "ModuleFileSystem.h"
#include "ModuleRenderer3D.h"
#include "GameObject.h"


ModuleResources::ModuleResources(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}


ModuleResources::~ModuleResources()
{
}

bool ModuleResources::Start()
{

	return true;
}

update_status ModuleResources::PreUpdate(float dt)
{
	
	return UPDATE_CONTINUE;
}

bool ModuleResources::CleanUp()
{
	
	return true;
}