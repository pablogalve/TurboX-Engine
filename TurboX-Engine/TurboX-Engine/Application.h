#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"
#include "Timer.h"
#include "./JSON/parson.h"
#include <vector>
#include <list>

class Module;

class ModuleFileSystem;
class ModuleWindow;
class ModuleInput;
class ModuleAudio;
class ModuleScene;
class ModuleEditor;
class ModuleRenderer3D;
class ModuleCamera3D;
class ModulePhysics3D;
class ModuleGui;
class ModuleScene;
class ModuleConsole;
class ModuleResources;

class Application
{
public:
	ModuleFileSystem* file_system = NULL;
	ModuleWindow* window = NULL;
	ModuleInput* input = NULL;
	ModuleAudio* audio = NULL;
	ModuleEditor* editor = NULL;
	ModuleRenderer3D* renderer3D = NULL;
	ModuleCamera3D* camera = NULL;
	ModulePhysics3D* physics = NULL;
	ModuleGui* gui = NULL;
	ModuleScene* scene = NULL;
	ModuleConsole* console = NULL;
	ModuleResources* resources = NULL;

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

extern Application* App;

#endif //__APPLICATION_H__