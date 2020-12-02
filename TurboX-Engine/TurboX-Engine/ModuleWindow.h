#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"
#include "SDL/include/SDL.h"
#include "Config_JSON.h"

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow(Application* app, bool start_enabled = true);

	// Destructor
	virtual ~ModuleWindow();

	bool Init()override;
	bool CleanUp()override;
	bool LoadSettings(Config* data)override;

	void SetTitle(const char* engine_name);
	void SetBrightness(float bright);
	void SetSize(uint w, uint h);
	void SetFullscreen(bool fullscreen);
	void SetResizable(bool resizable);
	void SetBorderless(bool borderless);
	void SetFullscreenDesktop(bool fullsdesktop);
	bool IsFullscreen() const { return _fullscreen; }
	bool IsResizable() const { return _resizable; }
	bool IsBorderless() const { return _borderless; }
	bool IsFullscreenDesktop() const { return _fullDesktop; }

	float GetBrightness() const { return _brightness; }
	void GetSize(int& h, int& w)const;

public:
	//The window we'll be rendering to
	SDL_Window* window;

	//The surface contained by the window
	SDL_Surface* screen_surface;


	bool _fullscreen;
	bool _resizable;
	bool _borderless;
	bool _fullDesktop;

	int _brightness = DEFAULT_BRIGHTNESS;
	uint _w;
	uint _h;
};

#endif // __ModuleWindow_H__