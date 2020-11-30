#include "Application.h"
#include "Module.h"
#include "ModuleFileSystem.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleEditor.h"
#include "ModuleEditor.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModulePhysics3D.h"
#include "ModuleGui.h"
#include "ModuleScene.h"
#include "ModuleConsole.h"
#include "ModuleResources.h"
#include "Config_JSON.h"

Application::Application()
{
	file_system = new ModuleFileSystem(this);
	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	audio = new ModuleAudio(this, true);
	editor = new ModuleEditor(this);
	renderer3D = new ModuleRenderer3D(this);
	camera = new ModuleCamera3D(this);
	physics = new ModulePhysics3D(this);
	gui = new ModuleGui(this);
	scene = new ModuleScene(this);
	console = new ModuleConsole();
	resources = new ModuleResources(this);
	
	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(file_system);
	AddModule(window);
	AddModule(camera);
	AddModule(input);
	AddModule(audio);
	AddModule(physics);
	AddModule(gui);
	AddModule(scene);
	AddModule(resources);

	// Scenes
	AddModule(editor);

	// Renderer last!
	AddModule(renderer3D);
}

Application::~Application()
{
	for (uint i = 0; i < modules_list.size(); i++)
	{
		delete modules_list[i];
	}

	modules_list.clear();
}

bool Application::Init()
{
	bool ret = true;

	char* buffer = nullptr;
	//uint size = file_system->Load("Library/Config/config.json", &buffer);
	const char* test = buffer;
	Config_JSON_Node config(test);
	Config_JSON_Node node = config.GetNode("modules_settings");
	// Call Init() in all modules	
	//Config_JSON_Array modules_json_array(config.GetArray("modules_settings"));


	for (uint i = 0; i < modules_list.size(); i++)
	{
		console->AddLog("Success with %s", modules_list[i]->name.c_str());
		
		ret = modules_list[i]->Init();
	}

	console->AddLog("-------------- Application Start --------------");

	// After all Init calls we call Start() in all modules
	for (int i = 0; i < modules_list.size() && ret == true; i++)
	{
		ret = modules_list[i]->Start();
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
	
	for (uint i = 0; i < modules_list.size() && ret == UPDATE_CONTINUE; i++)
	{
		ret = modules_list[i]->PreUpdate(dt);
	}
	for (uint i = 0; i < modules_list.size() && ret == UPDATE_CONTINUE; i++)
	{
		ret = modules_list[i]->Update(dt);
	}
	for (uint i = 0; i < modules_list.size() && ret == UPDATE_CONTINUE; i++)
	{
		ret = modules_list[i]->PostUpdate(dt);
	}

	if (closeApp)
		ret = UPDATE_STOP;

	FinishUpdate();
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;	

	for (uint i = 0; i < modules_list.size(); i++)
	{
		ret = modules_list[i]->CleanUp();
	}

	delete console;

	return ret;
}

void Application::CloseApp()
{
	closeApp = true;
}

void Application::AddModule(Module* mod)
{
	modules_list.push_back(mod);
}