#pragma once
#include "Module.h"
#include "Globals.h"


class DebugDrawer;

class ModulePhysics3D : public Module
{
public:
	ModulePhysics3D(Application* app, bool start_enabled = true);
	~ModulePhysics3D();

	bool Start()override;
	bool Init(JSON_Object* obj)override;
	update_status PreUpdate(float dt)override;
	update_status Update(float dt)override;
	update_status PostUpdate(float dt)override;
	bool CleanUp()override;

private:

	bool debug;

	DebugDrawer* debug_draw;
};