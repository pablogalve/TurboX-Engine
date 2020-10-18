#include "Application.h"

Application::Application()
{
	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	audio = new ModuleAudio(this, true);
	editor = new ModuleEditor(this);
	renderer3D = new ModuleRenderer3D(this);
	camera = new ModuleCamera3D(this);
	physics = new ModulePhysics3D(this);
	gui = new ModuleGui(this);
	importer = new ModuleImporter(this);
	console = new ModuleConsole();
	

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules	
	AddModule(window);
	AddModule(camera);
	AddModule(input);
	AddModule(audio);
	AddModule(importer);
	AddModule(physics);
	AddModule(gui);

	// Scenes
	AddModule(editor);

	// Renderer last!
	AddModule(renderer3D);
}

Application::~Application()
{
	for (std::list < Module* > ::reverse_iterator item = modules_list.rbegin(); item != modules_list.rend(); item++) {
		delete (*item);
	}
	modules_list.clear();
}

bool Application::Init()
{
	bool ret = true;

	JSON_Value* config;
	JSON_Object* objModules = nullptr;

	if (config = json_parse_file(CONFIG_FILE)) {
		
		JSON_Object* obj;
		JSON_Object* appObj;

		obj = json_value_get_object(config);
		appObj = json_object_get_object(obj, "App");

		const char* title = json_object_get_string(appObj, "Name");
		window->SetTitle((char*)title);

		objModules = obj;
		json_object_clear(appObj);
		obj = nullptr;
		json_object_clear(obj);

	}

	// Call Init() in all modules

	std::list<Module*>::iterator item = modules_list.begin();


	while (item != modules_list.end() && ret == true)
	{
		ret = (*item)->Init(json_object_get_object(objModules, (*item)->name.c_str()));
		item++;
	}

	console->AddLog("-------------- Application Start --------------");

	// After all Init calls we call Start() in all modules
	item = modules_list.begin();

	while (item != modules_list.end() && ret == true)
	{
		ret = (*item)->Start();
		item++;
	}
	
	json_object_clear(objModules);
	json_value_free(config);

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
	
	for (std::list<Module*>::iterator item = modules_list.begin(); item != modules_list.end() && ret == UPDATE_CONTINUE; item++) {
		ret = (*item)->PreUpdate(dt);
	}
	for (std::list<Module*>::iterator item = modules_list.begin(); item != modules_list.end() && ret == UPDATE_CONTINUE; item++) {
		ret = (*item)->Update(dt);
	}
	for (std::list<Module*>::iterator item = modules_list.begin(); item != modules_list.end() && ret == UPDATE_CONTINUE; item++) {
		ret = (*item)->PostUpdate(dt);
	}

	if (closeApp)
		ret = UPDATE_STOP;

	FinishUpdate();
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	
	std::list<Module*>::reverse_iterator item = modules_list.rbegin();

	while (item != modules_list.rend() && ret == true)
	{
		ret = (*item)->CleanUp();
		item++;
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