#pragma once
#include "Module.h"
#include "Globals.h"
#include "ModuleConsole.h"

#include <vector>

//Include WindowConfig panels
#include "W_About.h"
#include "W_Hierarchy.h"
#include "W_Configuration.h"
#include "W_Explorer.h"
#include "W_SceneWindow.h"
#include "W_Resources.h"
#include "W_Inspector.h"
#include "W_Theme.h"
#include "W_Toolbar.h"

typedef int GLint;

class ModuleEditor : public Module
{
public:
	ModuleEditor(Application* app, bool start_enabled = true);
	~ModuleEditor();

	bool Start() override;
	update_status Update(float dt) override;
	bool CleanUp() override;
	bool LoadSettings(Config* data)override;
	bool SaveSettings(Config* data)const override;

private:
	void CreateDockSpace();

	void ShowMenuBar();

public:
	W_About* about_window;
	W_Hierarchy* hierarchy_window;
	W_Explorer* explorer_window;
	W_SceneWindow* scene_window;
	W_Resources* resources_window;
	W_Inspector* inspector_window;
	W_Theme* theme_window;
	W_Configuration* config_window;
	W_Toolbar* toolbar_window;

	float sceneX = 0.0f;
	float sceneY = 0.0f;
	float sceneW = 0.0f;
	float sceneH = 0.0f;

private:
	bool showDemoWindow;
	bool showConfigurationWindow;
	bool showConsoleWindow;
	bool showToolbarWindow;
};
