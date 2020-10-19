#ifndef __CONFIGURATION_H_
#define __CONFIGURATION_H_

#include "WindowConfig.h"
#include "Module.h"
#include "Application.h"

#include <vector>

class Configuration : WindowConfig, public Module
{
public:
	Configuration(Application* app, bool start_enabled = true);
	~Configuration();

	void Draw() override;

	void SetShowWindow() override;
	bool GetShowWindow() override { return showWindow; };

	void GetHardwareCaps();
	void GetVramData(float& vram_budget, float& vram_usage, float& vram_available, float& vram_reserved);
private:
	std::vector<float> fps_log;
	std::vector<float> ms_log;

	std::vector<std::string> caps_log;
};

#endif // !__CONFIGURATION_H_
