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
	want_to_save = want_to_load = false;

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
	resources = new SceneImporter(this);
	
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

	LoadEngineNow();

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
	if (want_to_save == true) SaveEngineNow();
	if (want_to_load == true) LoadEngineNow();
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

void Application::LoadEngine()
{
	want_to_load = true;
}

void Application::SaveEngine()
{
	want_to_save = true;
}

bool Application::LoadEngineNow()
{
	bool ret = false;

	char* buffer = nullptr;
	uint size = App->file_system->readFile(CONFIG_FILE, &buffer);

	
	if (size < 0) {
		console->AddLog("Error loading file %s. All data not loaded.", CONFIG_FILE);
		return ret;
	}
	Config conf(buffer);
	RELEASE_ARRAY(buffer);

	Config appdata = conf.GetArray("App", 0);
	std::string name = appdata.GetString("Name", "NoName");
	SetEngineName(name.c_str());
	std::string org = appdata.GetString("Organization", "NoOrganization");
	SetOrganizationName(org.c_str());
	double version = appdata.GetNumber("Version", 0);
	SetEngineVersion(version);
	
	for (uint i = 0; i < modules_list.size(); i++)
	{
		Config elem = conf.GetArray(modules_list[i]->name.c_str(), 0);
		ret = modules_list[i]->LoadSettings(&elem);
		console->AddLog("Success with %s", modules_list[i]->name.c_str());
	}
	want_to_load = false;
	return ret;
}

bool Application::SaveEngineNow() const
{
	return false;
}

void Application::SetEngineName(const char* newName)
{
	engine_name = newName;
	window->SetTitle(engine_name.c_str());
}

const char* Application::GetEngineName() const
{
	return engine_name.c_str();
}

void Application::SetOrganizationName(const char* newName)
{
	organization_name = newName;
}

const char* Application::GetOrganizationName() const
{
	return organization_name.c_str();
}

void Application::SetEngineVersion(double newVersion)
{
	current_version = newVersion;
}

double Application::GetEngineVersion() const
{
	return current_version;
}


void Application::AddModule(Module* mod)
{
	modules_list.push_back(mod);
}