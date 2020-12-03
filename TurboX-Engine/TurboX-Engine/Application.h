#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"
#include "Timer.h"
#include "./JSON/parson.h"
#include "ImGuizmo/ImGuizmo.h"
#include <vector>
#include <list>
#include <string>

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
class SceneImporter;
class ModuleTimeManagement;

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
	SceneImporter* resources = NULL;
	ModuleTimeManagement* timeManagement = NULL;

private:
	float	time_scale = 1.0f;
	float	prevTime_scale = 1.f;
	int		time_scaleFrames = -1;
	Timer	ms_timer;
	float	dt;
	std::vector<Module*> modules_list;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();
	void CloseApp();

	void LoadEngine();
	void SaveEngine();

	bool LoadEngineNow();
	bool SaveEngineNow() const;

	void SetEngineName(const char* newName);
	const char* GetEngineName() const;
	void SetOrganizationName(const char* newName);
	const char* GetOrganizationName() const;
	void SetEngineVersion(double newVersion);
	double GetEngineVersion() const;

	const float GetTimeScale()const;
	void SetTimeScale(float ts, int frameNumber = -1);
	void PauseGame(bool pause);
private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
	bool closeApp = false;

private:
	mutable bool		want_to_save;
	bool				want_to_load;

	std::string			engine_name;
	std::string			organization_name;
	double				current_version;
};

extern Application* App;

#endif //__APPLICATION_H__