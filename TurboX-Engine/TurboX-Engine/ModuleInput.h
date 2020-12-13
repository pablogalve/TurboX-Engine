#pragma once
#include "Module.h"
#include "Globals.h"
#include "Config_JSON.h"
#include "ModuleGUI.h"
#include "Application.h"

#define MAX_MOUSE_BUTTONS 5

enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

struct Last_Inputs {
	std::string name; //Keybr, Mouse
	Uint8 keyboard_num; 
	std::string type; //UP, DOWN, REPEAT
	bool is_null = true;
	int size = 30;
	int last_input = 0;
};

enum class FileType {
	FBX,
	PNG,
	DDS,
	JPG,
	TGA,
	UNDEFINED
};

class ModuleInput : public Module
{
public:
	
	ModuleInput(Application* app, bool start_enabled = true);
	~ModuleInput();

	bool Init()override;
	update_status PreUpdate(float dt)override;
	bool CleanUp()override;

	KEY_STATE GetKey(int id) const
	{
		return keyboard[id];
	}
	KEY_STATE GetMouseButton(int id) const
	{
		if (App->gui->isMouseOnGUI())
			return KEY_IDLE;
		else
			return mouse_buttons[id];
	}
	
	int GetMouseX() const
	{
		return mouse_x;
	}
	int GetMouseY() const
	{
		return mouse_y;
	}
	int GetMouseZ() const
	{
		return mouse_z;
	}

	int GetMouseXMotion() const
	{
		return mouse_x_motion;
	}
	int GetMouseYMotion() const
	{
		return mouse_y_motion;
	}

	void AddLastInput(std::string name, Uint8 keyboard_num, std::string type);
	void PrintLastInputs();
	FileType GetFileType(std::string file);
public:
	Last_Inputs last_inputs[100];
private:
	KEY_STATE* keyboard;
	KEY_STATE mouse_buttons[MAX_MOUSE_BUTTONS];
	int mouse_x;
	int mouse_y;
	int mouse_z;
	int mouse_x_motion;
	int mouse_y_motion;
	//int mouse_z_motion;

	char* dropped_filedir;

};