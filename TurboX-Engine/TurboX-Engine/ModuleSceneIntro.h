#pragma once
#include "Module.h"
#include "Globals.h"

#include <vector>
#include <string>

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();
	float GetFPS();

private:

	void ShowMenuBar();
	void ShowDemoWindow();
	void ShowAboutWindow();
	void ShowConfigurationWindow();
	void GetHardwareCaps();
private:

	bool showDemoWindow;
	bool showAboutWindow;
	bool showConfigurationWindow;

	std::vector<float> fps_log;
	std::vector<float> ms_log;

	std::vector<std::string> caps_log;
};
