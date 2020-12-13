#ifndef __MODULE_GUI_H__
#define __MODULE_GUI_H__

#include "Module.h"

class ModuleGui : public Module
{
public:

	ModuleGui(Application* app, bool start_enabled = true);
	~ModuleGui();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	void Draw();
	bool CleanUp();
	bool isMouseOnGUI() const;

	bool hoveringScene = false;

};

#endif
