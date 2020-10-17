#pragma once

#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleEditor.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModulePhysics3D.h"
#include "ModuleGui.h"
#include "ModuleImporter.h"
#include "./JSON/parson.h"
#include <vector>
#include <list>

class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleEditor* editor;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	ModulePhysics3D* physics;
	ModuleGui* gui;
	ModuleConsole* console;
	ModuleImporter* importer;

private:

	Timer	ms_timer;
	float	dt;
	std::list<Module*> modules_list;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();
	void CloseApp();

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
	bool closeApp = false;
};