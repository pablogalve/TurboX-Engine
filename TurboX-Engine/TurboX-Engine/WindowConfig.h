#ifndef _WINDOWCONFIG_H_
#define _WINDOWCONFIG_H_

#include "ImGui/imgui.h"
#include "Globals.h"

class WindowConfig 
{
public:
	WindowConfig();
	~WindowConfig() {};

	virtual void Draw() { ; };

	virtual void SetShowWindow(bool new_value);
	virtual void SetShowWindow();
	virtual bool GetShowWindow() { return showWindow; };
protected:
	bool showWindow;
};

#endif // !_WINDOWCONFIG_H_
