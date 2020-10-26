#include "Globals.h"
#include "Application.h"
#include "ModulePhysics3D.h"
#include "ModuleInput.h"
#include "ModuleConsole.h"

// TODO 1: ...and the 3 libraries based on how we compile (Debug or Release)
// use the _DEBUG preprocessor define

ModulePhysics3D::ModulePhysics3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	debug_draw = NULL;
	debug = true;

	name = "Physics";
}

// Destructor
ModulePhysics3D::~ModulePhysics3D()
{
	delete debug_draw;
}

bool ModulePhysics3D::Init(JSON_Object* obj)
{
	bool ret = true;

	json_object_clear(obj);//clear obj to free memory
	return ret;
}

// ---------------------------------------------------------
bool ModulePhysics3D::Start()
{
	App->console->AddLog("Creating Physics environment");
	//LOG("Creating Physics environment");

	return true;
}

// ---------------------------------------------------------
update_status ModulePhysics3D::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

// ---------------------------------------------------------
update_status ModulePhysics3D::Update(float dt)
{
	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(debug == true)
	{
		
	}

	return UPDATE_CONTINUE;
}

// ---------------------------------------------------------
update_status ModulePhysics3D::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModulePhysics3D::CleanUp()
{
	App->console->AddLog("Destroying 3D Physics simulation");
	//LOG("Destroying 3D Physics simulation");

	return true;
}
