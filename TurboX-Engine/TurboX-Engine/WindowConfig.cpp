#include "WindowConfig.h"

WindowConfig::WindowConfig()
{
	showWindow = true;
}

void WindowConfig::SetShowWindow(bool new_value)
{
	showWindow = new_value;
}

void WindowConfig::SetShowWindow()
{
	showWindow = !showWindow;
}
