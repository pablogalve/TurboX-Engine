#pragma once
#include "Module.h"
#include "Globals.h"


class DebugDrawer;

class ModulePhysics3D : public Module
{
public:
	ModulePhysics3D(Application* app, bool start_enabled = true);
	~ModulePhysics3D();

	bool Start();
	bool Init(JSON_Object* obj);
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

private:

	bool debug;

	DebugDrawer* debug_draw;
};