#pragma once
#include "Module.h"
#include "Globals.h"
#include "ModuleConsole.h"

#include <vector>
#include <string>

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
	void ShowDemoWindow();
	void ShowAboutWindow();
	void ShowConfigurationWindow();
	void ShowHierarchyWindow();
	void ShowSceneWindow();
	void ShowToolbarWindow();
	void ShowInspectorWindow();
	void ShowExplorerWindow();
	void ShowResourcesWindow();

	void GetHardwareCaps();
	void GetVramData(float& vram_budget, float& vram_usage, float& vram_available, float& vram_reserved);
	
private:

	bool showDemoWindow;
	bool showAboutWindow;
	bool showConfigurationWindow;
	bool showConsoleWindow;
	bool showHierarchyWindow;
	bool showSceneWindow;
	bool showToolbarWindow;
	bool showInspectorWindow;
	bool showExplorerWindow;
	bool showResourcesWindow;

	std::vector<float> fps_log;
	std::vector<float> ms_log;

	std::vector<std::string> caps_log;	
};
