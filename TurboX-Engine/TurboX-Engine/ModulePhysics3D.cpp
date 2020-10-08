#include "Globals.h"
#include "Application.h"
#include "ModulePhysics3D.h"
#include "Primitive.h"

// TODO 1: ...and the 3 libraries based on how we compile (Debug or Release)
// use the _DEBUG preprocessor define

ModulePhysics3D::ModulePhysics3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	debug_draw = NULL;
	debug = true;

	// TODO 2: Create collision configuration, dispacher
	// broad _phase and solver

	//TODO 4: Uncomment the creation of the DebugDrawer
	//debug_draw = new DebugDrawer();
}

// Destructor
ModulePhysics3D::~ModulePhysics3D()
{
	delete debug_draw;
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
