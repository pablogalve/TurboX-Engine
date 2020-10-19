#pragma once
#include "Module.h"
#include "Globals.h"
#include "ModuleConsole.h"

#include <vector>
#include <string>

//Include WindowConfig panels
#include "About.h"
#include "Hierarchy.h"
//#include "Configuration.h"
#include "Explorer.h"
#include "SceneWindow.h"
#include "Resources.h"
#include "Inspector.h"

typedef int GLint;

class ModuleEditor : public Module
{
public:
	ModuleEditor(Application* app, bool start_enabled = true);
	~ModuleEditor();

	bool Start() override;
	update_status Update(float dt) override;
	bool CleanUp() override;

private:

	void ShowMenuBar();
	void ShowConfigurationWindow();
	void ShowToolbarWindow();	
	
	void GetHardwareCaps();
	void GetVramData(float& vram_budget, float& vram_usage, float& vram_available, float& vram_reserved);
private:
	About* about_window;
	Hierarchy* hierarchy_window;
	Explorer* explorer_window;
	SceneWindow* scene_window;
	Resources* resources_window;
	Inspector* inspector_window;
	//Configuration* config = new Configuration(App); //TODO: Gives error

	bool showDemoWindow;
	bool showConfigurationWindow;
	bool showConsoleWindow;
	bool showToolbarWindow;

	std::vector<float> fps_log;
	std::vector<float> ms_log;

	std::vector<std::string> caps_log;
};
