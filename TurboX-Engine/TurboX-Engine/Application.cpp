#include "Application.h"

Application::Application()
{
	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	audio = new ModuleAudio(this, true);
	scene_intro = new ModuleSceneIntro(this);
	renderer3D = new ModuleRenderer3D(this);
	camera = new ModuleCamera3D(this);
	physics = new ModulePhysics3D(this);
	gui = new ModuleGui(this);

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(camera);
	AddModule(input);
	AddModule(audio);
	AddModule(physics);
	AddModule(gui);

	// Scenes
	AddModule(scene_intro);

	// Renderer last!
	AddModule(renderer3D);
}

Application::~Application()
{
	std::vector<Module*>::reverse_iterator item = vector_modules.rbegin();

	while (item != vector_modules.rend())
	{
		delete* item;
		++item;
	}
}

bool Application::Init()
{
	bool ret = true;

	// Call Init() in all modules
	for (int i = 0; i < vector_modules.size() && ret == true; i++)
	{
		ret = vector_modules[i]->Init();
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");
	for (int i = 0; i < vector_modules.size() && ret == true; i++)
	{
		ret = vector_modules[i]->Start();
	}
	
	ms_timer.Start();
	return ret;
}

// ---------------------------------------------
void Application::PrepareUpdate()
{
	dt = (float)ms_timer.Read() / 1000.0f;
	ms_timer.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	PrepareUpdate();
	
	for (int i = 0; i < vector_modules.size() && ret == UPDATE_CONTINUE; i++)
	{
		ret = vector_modules[i]->PreUpdate(dt);
	}

	for (int i = 0; i < vector_modules.size() && ret == UPDATE_CONTINUE; i++)
	{
		ret = vector_modules[i]->Update(dt);
	}

	for (int i = 0; i < vector_modules.size() && ret == UPDATE_CONTINUE; i++)
	{
		ret = vector_modules[i]->PostUpdate(dt);
	}

	if (closeApp)
		ret = UPDATE_STOP;

	FinishUpdate();
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	
	for (int i = vector_modules.size() - 1; i > 0; i--)
	{
		vector_modules[i]->CleanUp();
	}

	return ret;
}

void Application::CloseApp()
{
	closeApp = true;
}

void Application::AddModule(Module* mod)
{
	vector_modules.push_back(mod);
}